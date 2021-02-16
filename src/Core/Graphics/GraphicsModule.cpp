#include"Config.h"

#include"Platform/Base/IRenderer.h"
#include"Platform/Base/IGraphics.h"
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
			m_dllLoader = new ::Platform::IO::DllLoader(moduleName);

			get = (Core::Graphics::GetGraphics)m_dllLoader->getProcess(TO_STRING(base_GetGraphics));
			release = (Core::Graphics::ReleaseGraphics)m_dllLoader->getProcess(TO_STRING(base_ReleaseGraphics));
			m_Graphics = get();
		}

		GraphicsModule::~GraphicsModule()
		{
			release(&m_Graphics);

			delete m_dllLoader;
		}

		void GraphicsModule::CreateRenderer(HWND hWnd, Platform::Graphics::detail::IRenderer** renderer)
		{
			m_Graphics->CreateRenderer(hWnd, renderer);
		}

		void GraphicsModule::ReleaseRenderer(Platform::Graphics::detail::IRenderer** renderer)
		{
			m_Graphics->ReleaseRenderer(renderer);
		}

	}
}
