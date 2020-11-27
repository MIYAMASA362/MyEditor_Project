#pragma once
#ifndef PLATFORM_NETWORK_H
#define PLATFORM_NETWORK_H

namespace Platform
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
				struct { unsigned char b0, b1, b2, b3; } S_un_b;
				struct { unsigned short w0, w1; } S_un_w;
				unsigned long S_addr;
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

		}// namespace Platform::Network::detail
	}// namespace Platform::Network
}// namespace Platform

#endif // ifndef PLATFORM_NETWORK_H