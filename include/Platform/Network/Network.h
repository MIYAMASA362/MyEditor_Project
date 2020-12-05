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

		// 
		enum class Flags
		{
			NONE			= 0,
			PASSIVE,
		};

		// 
		enum class CloseType
		{
			RECEIVE = 0,
			SEND,
			BOTH,
		};

		struct SocketInfo
		{
			Family		m_family		 = Family::IPv4;
			Protocol		m_protocol	 = Protocol::TCP;
			SocketType	m_socketType = SocketType::STREAM;
			PCSTR		m_address	 = NULL;
			PCSTR		m_port		 = NULL;
			Flags		m_flags		 = Flags::NONE;
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
				virtual int Create(ISocket** output, SocketInfo& info) = 0;
				// �\�P�b�g �R�Â�
				virtual int Bind(ISocket* iSocket) = 0;
				// �\�P�b�g �J��
				virtual int Listen(ISocket* iSocket) = 0;
				// �\�P�b�g �󂯓���
				virtual int Accept(ISocket* iSocket, ISocket** client) = 0;
				// �\�P�b�g �ڑ�
				virtual int Connect(ISocket* iSocket) = 0;
				// �\�P�b�g ��M
				virtual int Recv(ISocket* iSocket, char* buf, int buflen) = 0;
				// �\�P�b�g ���M
				virtual int Send(ISocket* iSocket, const char* buf, int sendlen) = 0;
				// �\�P�b�g ��
				virtual int Close(ISocket* iSocket,CloseType type) = 0;
				// �\�P�b�g �j��
				virtual void Release(ISocket** iSocket) = 0;

			};// class INetwork

		}// namespace Platform::Network::detail
	}// namespace Platform::Network
}// namespace Platform

#endif // ifndef PLATFORM_NETWORK_H