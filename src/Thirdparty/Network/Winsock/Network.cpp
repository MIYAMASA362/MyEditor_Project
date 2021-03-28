#include"pch.h"

//namespace Core
//{
//	namespace Network
//	{
//		namespace detail
//		{
//			EXTERN_C ENGINE_API ::Platform::Network::detail::INetwork* base_GetNetworkInterface()
//			{
//				return new ThirdParty::Core::WinsockNetwork();
//			}
//
//			EXTERN_C ENGINE_API void base_ReleaseNetworkInterface(::Platform::Network::detail::INetwork** instance)
//			{
//				delete dynamic_cast<ThirdParty::Core::WinsockNetwork*>(*instance);
//			}
//
//		}// namespace Core::Network::detail
//	}// namespace Core::Network
//}// namespace Core

namespace ThirdParty
{
	namespace Core
	{
		inline Socket* CastSocket(ISocket* iSocket){ return reinterpret_cast<Socket*>(iSocket);}

		void ReleaseSocket(Socket* pSocket)
		{
			closesocket(pSocket->m_MainSocket);
			freeaddrinfo(pSocket->m_AddrInfo);
		}

		void ErrorMessage(int code)
		{
			switch (code)
			{
			case WSASYSNOTREADY:
				LOG_ERROR("ネットワークサブシステムがネットワークへの接続を準備できていない。");
				break;
			case WSAVERNOTSUPPORTED:
				LOG_ERROR("要求されたWinsockのバージョンがサポートされていない。");
				break;
			case WSAEINPROGRESS:
				LOG_ERROR("ブロッキング操作の実行中であるか、またはサービスプロバイダがコールバック関数を処理している。");
				break;
			case WSAEPROCLIM:
				LOG_ERROR("Winsockが処理できる最大プロセス数に達した。");
				break;
			case WSAEFAULT:
				LOG_ERROR("第二引数であるlpWSADataは有効なポインタではない。")
				break;
			default:
				break;
			}
		}

		int ConvertFamily(::Platform::Network::Family family)
		{
			if (family == ::Platform::Network::Family::IPv4)
				return AF_INET;
			else
				return AF_INET6;
		}

		int ConvertSockType(::Platform::Network::SocketType socketType)
		{
			if (socketType == ::Platform::Network::SocketType::STREAM)
				return SOCK_STREAM;
			else
				return SOCK_DGRAM;
		}

		int ConvertProtocol(::Platform::Network::Protocol protocol)
		{
			if (protocol == ::Platform::Network::Protocol::TCP)
				return IPPROTO_TCP;
			else
				return IPPROTO_UDP;
		}

		int ConvertFlags(::Platform::Network::Flags flags)
		{
			if (flags == ::Platform::Network::Flags::NONE)
				return 0;
			else if (flags == ::Platform::Network::Flags::PASSIVE)
				return AI_PASSIVE;
			return 0;
		}

		int ConvertCloseType(::Platform::Network::CloseType type)
		{
			if (type == ::Platform::Network::CloseType::RECEIVE)
				return SD_RECEIVE;
			else if (type == ::Platform::Network::CloseType::SEND)
				return SD_SEND;
			return SD_BOTH;
		}

		WinsockNetwork::WinsockNetwork()
		{
			m_wsaData = {};
		}

		WinsockNetwork::~WinsockNetwork()
		{

		}

		int WinsockNetwork::Startup()
		{
			LOG_DEBUG("Network Startup...");
			int iResult = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
			if (iResult != 0)
			{
				ErrorMessage(iResult);
				return Platform::Network::FAILED;
			}
			return Platform::Network::SUCCESS;
		}

		void WinsockNetwork::Cleanup()
		{
			LOG_DEBUG("Network Cleanup...");
			WSACleanup();
		}

		int WinsockNetwork::Create(ISocket** output, SocketInfo &info)
		{
			Socket* pSocket = new Socket();

			addrinfo hints;
			ZeroMemory(&hints, sizeof(addrinfo));
			hints.ai_family	= ConvertFamily(info.m_family);
			hints.ai_socktype	= ConvertSockType(info.m_socketType);
			hints.ai_protocol	= ConvertProtocol(info.m_protocol);
			hints.ai_flags = ConvertFlags(info.m_flags);

			addrinfo** result = &pSocket->m_AddrInfo;

			if(getaddrinfo(info.m_address,info.m_port,&hints, &pSocket->m_AddrInfo) != 0)
			{
				LOG_ERROR("getaddrinfo failed with error : %d\n",WSAGetLastError());
				delete pSocket;
				return Platform::Network::FAILED;
			}

			pSocket->m_MainSocket = socket((*result)->ai_family,(*result)->ai_socktype,(*result)->ai_protocol);
			if(pSocket->m_MainSocket == INVALID_SOCKET)
			{
				LOG_ERROR("Error at socket() : %d",WSAGetLastError());
				delete pSocket;
				return Platform::Network::FAILED;
			}
			
			*output = pSocket;
			return Platform::Network::SUCCESS;
		}

		int WinsockNetwork::Bind(ISocket * iSocket)
		{
			Socket* pSocket = CastSocket(iSocket);
			if(bind(pSocket->m_MainSocket,pSocket->m_AddrInfo->ai_addr,(int)pSocket->m_AddrInfo->ai_addrlen) == SOCKET_ERROR)		
			{
				LOG_ERROR("bind failed with error : \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}

			return Platform::Network::SUCCESS;
		}

		int WinsockNetwork::Listen(ISocket* iSocket)
		{
			Socket* pSocket = CastSocket(iSocket);
			if(listen(pSocket->m_MainSocket,SOMAXCONN) == SOCKET_ERROR)
			{
				LOG_ERROR("listen failed with error : %d \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}

			return Platform::Network::SUCCESS;
		}

		int WinsockNetwork::Accept(ISocket* iSocket,ISocket** client)
		{
			Socket* pSocket = CastSocket(iSocket);
			int len = (int)pSocket->m_AddrInfo->ai_addrlen;
			Socket* pClient = new Socket();
			pClient->m_MainSocket = accept(pSocket->m_MainSocket, pSocket->m_AddrInfo->ai_addr, &len);
			if(pClient->m_MainSocket == INVALID_SOCKET)
			{
				LOG_ERROR("accept failed with error : %d \n", WSAGetLastError());
				delete pClient;
				return Platform::Network::FAILED;
			}
			*client = pClient;
			return Platform::Network::SUCCESS;
		}

		int WinsockNetwork::Connect(ISocket* iSocket)
		{
			Socket* pSocket = CastSocket(iSocket);
			if(connect(pSocket->m_MainSocket,pSocket->m_AddrInfo->ai_addr,(int)pSocket->m_AddrInfo->ai_addrlen) == INVALID_SOCKET)
			{
				LOG_ERROR("connect failed with error : %d \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}

			return Platform::Network::SUCCESS;
		}

		int WinsockNetwork::Recv(ISocket* iSocket, char* buf, int buflen)
		{
			Socket* pSocket = CastSocket(iSocket);
			int len = recv(pSocket->m_MainSocket, buf, buflen, 0);
			if(len < 0)
			{
				LOG_ERROR("recv failed with error : %d \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}
			return len;
		}

		int WinsockNetwork::Send(ISocket* iSocket,const char* buf, int sendlen)
		{
			Socket* pSocket = CastSocket(iSocket);
			int len = send(pSocket->m_MainSocket, buf, sendlen, 0);
			if(len == SOCKET_ERROR)
			{
				LOG_ERROR("send failed with error : %d \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}

			return len;
		}

		int WinsockNetwork::Close(ISocket* iSocket,Platform::Network::CloseType type)
		{
			Socket* pSocket = CastSocket(iSocket);
			if(shutdown(pSocket->m_MainSocket,SD_BOTH) == SOCKET_ERROR)
			{
				LOG_ERROR("shutdown failed with error : %d \n",WSAGetLastError());
				return Platform::Network::FAILED;
			}

			return Platform::Network::SUCCESS;
		}

		void WinsockNetwork::Release(ISocket** iSocket)
		{
			Socket* pSocket = CastSocket(*iSocket);
			closesocket(pSocket->m_MainSocket);
			freeaddrinfo(pSocket->m_AddrInfo);
			delete pSocket;
		}

	}// namespace ThirdParty::Core
}// namespace ThirdParty