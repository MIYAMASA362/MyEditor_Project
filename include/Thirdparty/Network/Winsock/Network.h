#pragma once
#ifndef THIRDPARTY_NETWORK_H
#define THIRDPARTY_NETWORK_H

namespace ThirdParty
{
	namespace Core
	{
		using SocketInfo = ::Platform::Network::SocketInfo;
		using ISocket = ::Platform::Network::detail::ISocket;
		using INetwork = ::Platform::Network::detail::INetwork;

		/**
		* @class    Socket
		* @brief    Socket�ݒ�
		*/
		class Socket :public ISocket
		{
		public:
			SOCKET m_MainSocket  = INVALID_SOCKET;
			addrinfo* m_AddrInfo = NULL;

		private:

		};// class Socket

		/**
		* @class    WinsockNetwork
		* @brief    Winsock�p�̃l�b�g���[�N
		*/
		class WinsockNetwork : public INetwork
		{
		public:
			WinsockNetwork();
			virtual ~WinsockNetwork();

			// ������
			virtual int Startup() override;
			// �I��
			virtual void Cleanup() override;
			
			// �\�P�b�g �쐬
			virtual int Create(ISocket** output, SocketInfo& info) override;
			// �\�P�b�g �R�Â�
			virtual int Bind(ISocket* iSocket) override;
			// �\�P�b�g �J��
			virtual int Listen(ISocket* iSocket) override;
			// �\�P�b�g �󂯓���
			virtual int Accept(ISocket* iSocket, ISocket** client) override;
			// �\�P�b�g �ڑ�
			virtual int Connect(ISocket* iSocket) override;
			// �\�P�b�g ��M
			virtual int Recv(ISocket* iSocket, char* buf, int buflen) override;
			// �\�P�b�g ���M
			virtual int Send(ISocket* iSocket, const char* buf, int sendlen) override;
			// �\�P�b�g ��
			virtual int Close(ISocket* iSocket,Platform::Network::CloseType type) override;
			// �\�P�b�g �j��
			virtual void Release(ISocket** iSocket) override;

		private:
			WSADATA m_wsaData;

		};// class WinsockNetwork

	}// namespace ThirdParty::Core
}// namespace ThirdParty

#endif// ifndef THIRDPARTY_WINSOCK_H