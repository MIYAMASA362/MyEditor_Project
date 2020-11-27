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

				// 受け入れ
				//	クライアントからの接続待機
				virtual void Accept() = 0;

				// 接続 
				//	サーバへの接続
				virtual void Conect() = 0;
				
				// 受信
				//	データ受信
				virtual void Recv() = 0;

				// 送信
				//	データ送信
				virtual void Send() = 0;

				// 接続終了
				virtual void Close() = 0;

				// 終了処理
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