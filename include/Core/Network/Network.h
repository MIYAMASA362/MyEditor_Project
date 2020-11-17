#pragma once

/*
*	Winsock Document
*	・https://docs.microsoft.com/en-us/windows/win32/api/winsock2/
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
		/* ポート番号 */
		typedef int Port;

		/* アドレス */
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

			// 接続
			virtual void Accept();

			// 受信
			virtual void Recv();

			// 送信
			virtual void Send(const char* buffer,int length);

			// Socketを設定する
			void SetByIPAddress(const char* IPAddress,Port port);

			void SetSocket(Port port);
		
		private:
			// 初期化
			int Startup();
			
			// ソケット 生成
			int Create(SOCKET* output);

			// ソケット アドレス関連付け
			int Bind();

			// ソケット 接続待機
			int Listen();
			
			// ソケット 破棄
			void Close();
			
			// 終了処理
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