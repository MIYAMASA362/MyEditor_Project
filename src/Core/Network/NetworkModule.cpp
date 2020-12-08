#include "stdafx.h"

#include "Platform/Base/INetwork.h"
#include "Platform/IO/DllLoader.h"
#include "Platform/Module/Module.h"

#include "Core/Network/NetworkModule.h"

namespace Core
{
	namespace Network
	{
		NetworkModule::NetworkModule(const char * moduleName)
		{
			m_dllLoader = new ::Platform::DllLoader(moduleName);

			get = (Core::Network::detail::GetNetworkInterface)m_dllLoader->getProcess(TO_STRING(base_GetNetworkInterface));
			release = (Core::Network::detail::ReleaseNetworkInterface)m_dllLoader->getProcess(TO_STRING(base_ReleaseNetworkInterface));
		}

		NetworkModule::~NetworkModule()
		{
			delete m_dllLoader;
		}

		void NetworkModule::CreateNetwork(::Platform::Network::detail::INetwork ** network)
		{
			*network = get();
		}

		void NetworkModule::ReleaseNetwork(::Platform::Network::detail::INetwork ** instance)
		{
			release(instance);
		}

	}// namespace Core::Network
}// namespace Core