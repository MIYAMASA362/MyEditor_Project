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
		// IP�A�h���X�̎擾
		PCSTR GetIPAddress(sockaddr_in& sock,char* buffer,size_t size)
		{
			return inet_ntop(sock.sin_family,&sock.sin_addr,buffer,size);
		}


		// �R���X�g���N�^
		Sock::Sock()
		{
			m_Data = {};
			m_ClientSocket = INVALID_SOCKET;
		}

		// �f�X�g���N�^
		Sock::~Sock()
		{
		}

		// �ڑ�
		void Sock::Accept()
		{
			int len = sizeof(m_Client);
			m_ClientSocket = accept(m_Socket,(struct sockaddr*)&m_Client,&len);
		}

		// ��M
		void Sock::Recv()
		{

		}

		// ���M
		void Sock::Send(const char* buffer,int length)
		{
			if (m_ClientSocket == INVALID_SOCKET) return;
			int result = send(m_ClientSocket,buffer,length,0);
			if (result == SOCKET_ERROR) LOG_ERROR("send function failed with error : %d", WSAGetLastError());
		}

		// Socket�ݒ�
		void Sock::SetByIPAddress(const char * IPAddress, Port port)
		{
			int result;
			m_Addr.sin_family = AF_INET;
			m_Addr.sin_port = htons(port);
			result = inet_pton(m_Addr.sin_family, IPAddress, &m_Addr.sin_addr);
			if (result != 0) LOG_ERROR("inet_pton function failed with error : %d", WSAGetLastError());
		}

		// Socket�ݒ�
		void Sock::SetSocket(Port port)
		{
			m_Addr.sin_family = AF_INET;
			m_Addr.sin_port = htons(port);
			m_Addr.sin_addr.S_un.S_addr = INADDR_ANY;
		}

		// ������
		int Sock::Startup()
		{
			int result = WSAStartup(MAKEWORD(2, 0),&m_Data);
			if(result != 0)
			{
				switch (result)
				{
				case WSASYSNOTREADY:
					LOG_ERROR("�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ��B");
					break;
				case WSAVERNOTSUPPORTED:
					LOG_ERROR("�v�����ꂽWinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ��B");
					break;
				case WSAEINPROGRESS:
					LOG_ERROR("�u���b�L���O����̎��s���ł��邩�A�܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���B");
					break;
				case WSAEPROCLIM:
					LOG_ERROR("Winsock�������ł���ő�v���Z�X���ɒB�����B");
					break;
				case WSAEFAULT:
					LOG_ERROR("�������ł���lpWSAData�͗L���ȃ|�C���^�ł͂Ȃ��B")
						break;
				default:
					break;
				}
			}

			return result;
		}

		// �\�P�b�g����
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

		// �\�P�b�g �A�h���X�֘A�t��
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

		// �\�P�b�g �ڑ��ҋ@
		int Sock::Listen()
		{
			int result = listen(m_Socket,5);
			if (result == SOCKET_ERROR) LOG_ERROR("Listen function failed with error: %d",WSAGetLastError());
			return result;
		}

		// �\�P�b�g �j��
		void Sock::Close()
		{
			int result;
			result = closesocket(m_Socket);
			if (result == SOCKET_ERROR) LOG_ERROR("closeSocket function failed with error: %d",WSAGetLastError());
		}

		// �I������
		void Sock::Cleanup()
		{
			WSACleanup();
		}

	}
}// namespace Core::Network