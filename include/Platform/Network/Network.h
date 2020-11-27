#pragma once
#ifndef PLATFORM_NETWORK_H
#define PLATFORM_NETWORK_H

namespace Platform
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

		}// namespace Platform::Network::detail
	}// namespace Platform::Network
}// namespace Platform

#endif // ifndef PLATFORM_NETWORK_H