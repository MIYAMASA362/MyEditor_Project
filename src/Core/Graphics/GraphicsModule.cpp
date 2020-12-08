#include"stdafx.h"

#include"Platform/Base/IRenderer.h"
#include"Platform/IO/DllLoader.h"
#include"Platform/Module/Module.h"

#include"Core/Graphics/GraphicsModule.h"
#include"Core/Graphics/GraphicsFactory.h"

namespace Core
{
	namespace Graphics
	{
		GraphicsModule::GraphicsModule(const char* moduleName)
		{
			m_dllLoader = new ::Platform::DllLoader(moduleName);

			get = (Core::Graphics::detail::GetGraphicsFactory)m_dllLoader->getProcess(TO_STRING(base_GetGraphicsFactory));
			release = (Core::Graphics::detail::ReleaseGraphicsFactory)m_dllLoader->getProcess(TO_STRING(base_ReleaseGraphicsFactory));

			m_Factory = get();
		}

		GraphicsModule::~GraphicsModule()
		{
			release(&m_Factory);

			delete m_dllLoader;
		}

		void GraphicsModule::CreateRenderer(HWND hWnd, Platform::Graphics::detail::IRenderer** renderer)
		{
			m_Factory->create(hWnd, renderer);
		}

		void GraphicsModule::ReleaseRenderer(Platform::Graphics::detail::IRenderer** renderer)
		{
			m_Factory->release(renderer);
		}
	}
}
