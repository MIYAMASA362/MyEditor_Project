#pragma once

/*
*	Winsock Document
*	�Ehttps://docs.microsoft.com/en-us/windows/win32/api/winsock2/
*
*/


#ifndef CORE_NETWORK_H
#define CORE_NETWORK_H

#define CLIENT_MAX 10
#define SEND_MAX 1024

namespace Core
{
	namespace Network
	{
		/* �|�[�g�ԍ� */
		typedef int Port;

		/* �A�h���X */
		typedef char Address[32];

		/**
		* @class    Sock
		* @brief    Enum Description
		*/
		class Sock
		{
		public:
			Sock();
			virtual ~Sock();

			// �ڑ�
			virtual void Accept();

			// ��M
			virtual void Recv();

			// ���M
			virtual void Send(const char* buffer,int length);

			// Socket��ݒ肷��
			void SetByIPAddress(const char* IPAddress,Port port);

			void SetSocket(Port port);
		
		private:
			// ������
			int Startup();
			
			// �\�P�b�g ����
			int Create(SOCKET* output);

			// �\�P�b�g �A�h���X�֘A�t��
			int Bind();

			// �\�P�b�g �ڑ��ҋ@
			int Listen();
			
			// �\�P�b�g �j��
			void Close();
			
			// �I������
			void Cleanup();


			WSADATA m_Data;

			sockaddr_in m_Addr;
			SOCKET m_Socket;

			sockaddr_in m_Client;
			SOCKET m_ClientSocket;
		};

	}// namespace Network
}// namespace Core

#endif