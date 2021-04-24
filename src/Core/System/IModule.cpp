#include"Config.h"

#include"Platform/IO/DllLoader.h"

#include"Core/System/IModule.h"

namespace Core
{
	IModule::IModule(const char* moduleName)
		:
		m_dllLoader(nullptr)
	{
		m_dllLoader = new Platform::IO::DllLoader(moduleName);
	}

	IModule::~IModule()
	{
		if(m_dllLoader != nullptr)
		{
			delete m_dllLoader;
			m_dllLoader = nullptr; 
		}
	}
}