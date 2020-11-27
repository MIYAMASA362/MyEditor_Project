#include "stdafx.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Core/Base/Logger.h"
#include "Core/Base/Assert.h"

#include "Core/Network/Network.h"

/*
*	Sock
*
*/
namespace Core
{
	namespace Network
	{
		// IPアドレスの取得
		PCSTR GetIPAddress(sockaddr_in& sock,char* buffer,size_t size)
		{
			return inet_ntop(sock.sin_family,&sock.sin_addr,buffer,size);
		}


		// コンストラクタ
		Sock::Sock()
		{
			m_Data = {};
			m_ClientSocket = INVALID_SOCKET;
		}

		// デストラクタ
		Sock::~Sock()
		{
		}

		// 接続
		void Sock::Accept()
		{
			int len = sizeof(m_Client);
			m_ClientSocket = accept(m_Socket,(struct sockaddr*)&m_Client,&len);
		}

		// 受信
		void Sock::Recv()
		{

		}

		// 送信
		void Sock::Send(const char* buffer,int length)
		{
			if (m_ClientSocket == INVALID_SOCKET) return;
			int result = send(m_ClientSocket,buffer,length,0);
			if (result == SOCKET_ERROR) LOG_ERROR("send function failed with error : %d", WSAGetLastError());
		}

		// Socket設定
		void Sock::SetByIPAddress(const char * IPAddress, Port port)
		{
			int result;
			m_Addr.sin_family = AF_INET;
			m_Addr.sin_port = htons(port);
			result = inet_pton(m_Addr.sin_family, IPAddress, &m_Addr.sin_addr);
			if (result != 0) LOG_ERROR("inet_pton function failed with error : %d", WSAGetLastError());
		}

		// Socket設定
		void Sock::SetSocket(Port port)
		{
			m_Addr.sin_family = AF_INET;
			m_Addr.sin_port = htons(port);
			m_Addr.sin_addr.S_un.S_addr = INADDR_ANY;
		}

		// 初期化
		int Sock::Startup()
		{
			int result = WSAStartup(MAKEWORD(2, 0),&m_Data);
			if(result != 0)
			{
				switch (result)
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

			return result;
		}

		// ソケット生成
		int Sock::Create(SOCKET* output)
		{
			int result = 0;
			(*output) = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
			if((*output) == INVALID_SOCKET)
			{
				LOG_ERROR("socket function fialed with error : %d",WSAGetLastError());
				return -1;
			}
			return result;
		}

		// ソケット アドレス関連付け
		int Sock::Bind()
		{
			int result = bind(m_Socket,(struct sockaddr*)&m_Addr,sizeof(m_Addr));
			if(result == SOCKET_ERROR)
			{
				LOG_ERROR("bind function failed with eroor : %d",WSAGetLastError());
				Close();
				Cleanup();
			}

			return result;
		}

		// ソケット 接続待機
		int Sock::Listen()
		{
			int result = listen(m_Socket,5);
			if (result == SOCKET_ERROR) LOG_ERROR("Listen function failed with error: %d",WSAGetLastError());
			return result;
		}

		// ソケット 破棄
		void Sock::Close()
		{
			int result;
			result = closesocket(m_Socket);
			if (result == SOCKET_ERROR) LOG_ERROR("closeSocket function failed with error: %d",WSAGetLastError());
		}

		// 終了処理
		void Sock::Cleanup()
		{
			WSACleanup();
		}

	}
}// namespace Core::Network