#include "stdafx.h"

namespace Core
{
	GraphicsModule::GraphicsModule(const char * moduleName)
	{
		m_dllLoader = new Core::DllLoader(moduleName);

		get = (Core::GetGraphicsFactory)m_dllLoader->getProcess("base_GetGraphicsFactory");
		release = (Core::ReleaseGraphicsFactory)m_dllLoader->getProcess("base_ReleaseGraphicsFactory");

		m_Factory = get();
	}

	GraphicsModule::~GraphicsModule()
	{
		release(&m_Factory);

		delete m_dllLoader;
	}

	void Core::GraphicsModule::CreateRenderer(HWND hWnd,Platform::detail::IRenderer ** renderer)
	{
		m_Factory->create(hWnd,renderer);
	}

	void GraphicsModule::ReleaseRenderer(Platform::detail::IRenderer ** renderer)
	{
		m_Factory->release(renderer);
	}

}//namespace Core
