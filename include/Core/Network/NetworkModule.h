#pragma once
#ifndef CORE_NETWORKMODULE_H
#define CORE_NETWORKMODULE_H

namespace Core
{
	class DllLoader;

	namespace Network
	{
		namespace detail
		{
			typedef ::Platform::Network::detail::INetwork* (*GetNetworkInterface)();
			EXTERN_C ENGINE_API ::Platform::Network::detail::INetwork* base_GetNetworkInterface();

			typedef void(*ReleaseNetworkInterface)(::Platform::Network::detail::INetwork** instance);
			EXTERN_C ENGINE_API void base_ReleaseNetworkInterface(::Platform::Network::detail::INetwork** instance);

		}// namespace Core::Network::detail

		/**
		* @class    NetworkModule
		* @brief    ネットワークモジュール
		*/
		class NetworkModule : public ::Platform::detail::IModule
		{
		private:
			::Platform::IO::DllLoader* m_dllLoader;

			detail::GetNetworkInterface get;
			detail::ReleaseNetworkInterface release;

		public:
			NetworkModule(const char* moduleName);
			virtual ~NetworkModule();

			void CreateNetwork(::Platform::Network::detail::INetwork** network);
			void ReleaseNetwork(::Platform::Network::detail::INetwork** network);

		};// class NetworkModule

	}// namespace Network
}// namespace Core

#endif