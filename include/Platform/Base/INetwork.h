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
			NONE = 0,
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
			Family		m_family = Family::IPv4;
			Protocol	m_protocol = Protocol::TCP;
			SocketType	m_socketType = SocketType::STREAM;
			PCSTR		m_address = NULL;
			PCSTR		m_port = NULL;
			Flags		m_flags = Flags::NONE;
		};

		// ISocket
		class ISocket
		{
		protected:
			ISocket() ENGINE_DEFAULT;
			virtual ~ISocket() ENGINE_DEFAULT;

		};// class ISocket

		// Network
		class INetwork
		{
		protected:
			INetwork() ENGINE_DEFAULT;
			virtual ~INetwork() ENGINE_DEFAULT;

		public:

			// ������
			virtual int Startup(
			) ENGINE_PURE;

			// �I������
			virtual void Cleanup(
			) ENGINE_PURE;

			// �\�P�b�g �쐬
			virtual int Create(
				OUT ISocket** output,
				IN SocketInfo& info
			) ENGINE_PURE;

			// �\�P�b�g �R�Â�
			virtual int Bind(
				IN ISocket* iSocket
			) ENGINE_PURE;

			// �\�P�b�g �J��
			virtual int Listen(
				IN ISocket* iSocket
			) ENGINE_PURE;

			// �\�P�b�g �󂯓���
			virtual int Accept(
				IN ISocket* iSocket,
				OUT ISocket** client
			) ENGINE_PURE;

			// �\�P�b�g �ڑ�
			virtual int Connect(
				IN ISocket* iSocket
			) ENGINE_PURE;

			// �\�P�b�g ��M
			virtual int Recv(
				IN ISocket* iSocket,
				IN char* buf,
				IN int buflen
			) ENGINE_PURE;

			// �\�P�b�g ���M
			virtual int Send(
				IN ISocket* iSocket,
				IN const char* buf,
				IN int sendlen
			) ENGINE_PURE;

			// �\�P�b�g ��
			virtual int Close(
				IN ISocket* iSocket,
				IN CloseType type
			) ENGINE_PURE;

			// �\�P�b�g �j��
			virtual void Release(
				IN ISocket** iSocket
			) ENGINE_PURE;

		};// class INetwork

	}// namespace Platform::Network
}// namespace Platform

#endif // ifndef PLATFORM_NETWORK_H