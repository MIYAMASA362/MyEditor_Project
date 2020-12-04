#pragma once
#ifndef PLATFORM_NETWORK_H
#define PLATFORM_NETWORK_H

namespace Platform
{
	namespace Network
	{
		constexpr int FAILED = -1;
		constexpr int SUCCESS = 0;

		// Family
		enum class Family
		{
			IPv4,
			IPv6
		};

		// SocketType
		enum class SocketType
		{
			STREAM,
			DGRAM
		};

		// Protocol
		enum class Protocol
		{
			TCP,
			UDP
		};

		// NetType
		enum class NetType
		{
			Server,
			Client
		};

		struct SocketInfo
		{
			Family		m_family	 = Family::IPv4;
			Protocol	m_protocol	 = Protocol::TCP;
			SocketType	m_socketType = SocketType::STREAM;
			LPSTR		m_Address	 = NULL;
			LPSTR		m_Port		 = NULL;
		};

		namespace detail
		{
			// ISocket
			class ENGINE_API ISocket
			{
			private:

			public:
				

			};// class IScoket

			// Network
			/*
				Socket�̏����g��
			*/
			class ENGINE_API INetwork
			{
			public:
				INetwork() = default;
				virtual ~INetwork() = default;

				// ������
				virtual int Startup() = 0;
				// �I������
				virtual void Cleanup() = 0;

				// �\�P�b�g �쐬
				virtual int Create(ISocket* output, SocketInfo& info) = 0;
				// �\�P�b�g �R�Â�
				virtual int Bind(ISocket* iSocket) = 0;
				// �\�P�b�g �J��
				virtual int Listen(ISocket* iSocket) = 0;
				// �\�P�b�g �󂯓���
				virtual int Accept(ISocket* iSocket) = 0;
				// �\�P�b�g �ڑ�
				virtual int Connect(ISocket* iSocket) = 0;
				// �\�P�b�g ��M
				virtual int Recv(ISocket* iSocket, char* buf, int buflen) = 0;
				// �\�P�b�g ���M
				virtual int Send(ISocket* iSocket, char* buf, int sendlen) = 0;
				// �\�P�b�g ��
				virtual int Close(ISocket* iSocket) = 0;
				// �\�P�b�g �j��
				virtual void Release(ISocket* iSocket) = 0;

			};// class INetwork

		}// namespace Platform::Network::detail
	}// namespace Platform::Network
}// namespace Platform

#endif // ifndef PLATFORM_NETWORK_H