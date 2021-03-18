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
		* @brief    Socket設定
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
		* @brief    Winsock用のネットワーク
		*/
		class WinsockNetwork : public INetwork
		{
		public:
			WinsockNetwork();
			virtual ~WinsockNetwork();

			// 初期化
			virtual int Startup() override;
			// 終了
			virtual void Cleanup() override;
			
			// ソケット 作成
			virtual int Create(ISocket** output, SocketInfo& info) override;
			// ソケット 紐づけ
			virtual int Bind(ISocket* iSocket) override;
			// ソケット 開放
			virtual int Listen(ISocket* iSocket) override;
			// ソケット 受け入れ
			virtual int Accept(ISocket* iSocket, ISocket** client) override;
			// ソケット 接続
			virtual int Connect(ISocket* iSocket) override;
			// ソケット 受信
			virtual int Recv(ISocket* iSocket, char* buf, int buflen) override;
			// ソケット 送信
			virtual int Send(ISocket* iSocket, const char* buf, int sendlen) override;
			// ソケット 閉鎖
			virtual int Close(ISocket* iSocket,Platform::Network::CloseType type) override;
			// ソケット 破棄
			virtual void Release(ISocket** iSocket) override;

		private:
			WSADATA m_wsaData;

		};// class WinsockNetwork

	}// namespace ThirdParty::Core
}// namespace ThirdParty

#endif// ifndef THIRDPARTY_WINSOCK_H