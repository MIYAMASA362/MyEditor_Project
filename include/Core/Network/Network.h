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

		// Family
		enum Family
		{
			IPv4,
			IPv6
		};

		// SocketType
		enum SocketType
		{
			STREAM,
			DGRAM
		};

		// Protocol
		enum Protocol
		{
			TCP,
			UDP
		};

		// IPv4 Address Code
		struct Address
		{
			union {
				struct { UCHAR b0, b1, b2, b3; } S_un_b;
				struct { USHORT w0, w1; } S_un_w;
				ULONG S_addr;
			}S_un;
		};

#define CONECT_ANY			(ULONG)0x00000000
#define CONECT_LOOPBACK		(ULONG)0x7f000001
#define CONECT_BROADCAST	(ULONG)0xffffffff
#define CONECT_NONE			(ULONG)0xffffffff

		// NetType
		enum NetType
		{
			Server,
			Client
		};

		namespace detail
		{
			// Network Scoket
			class ISocket
			{
			private:

			public:
				Family m_Family;
				Protocol m_Protocol;
			};

			// Network
			class INetwork
			{
			private:

			public:

				// �󂯓���
				//	�N���C�A���g����̐ڑ��ҋ@
				virtual void Accept() = 0;

				// �ڑ� 
				//	�T�[�o�ւ̐ڑ�
				virtual void Conect() = 0;
				
				// ��M
				//	�f�[�^��M
				virtual void Recv() = 0;

				// ���M
				//	�f�[�^���M
				virtual void Send() = 0;

				// �ڑ��I��
				virtual void Close() = 0;

				// �I������
				virtual void Cleanup() = 0;

			};// class INetwork

		}// namespace Core::Network::detail

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