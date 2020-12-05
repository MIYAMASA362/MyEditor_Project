#include "stdafx.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Platform/Network/Network.h"

#include "Core/IO/DllLoader.h"

#include "Core/Base/Logger.h"
#include "Core/Base/Assert.h"

#include "Core/Module/Module.h"
#include "Core/Network/Network.h"

namespace Core
{
	namespace Network
	{
		NetworkModule::NetworkModule(const char * moduleName)
		{
			m_dllLoader = new Core::DllLoader(moduleName);

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