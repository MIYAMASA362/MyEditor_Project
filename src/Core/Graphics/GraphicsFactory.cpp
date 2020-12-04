#include "stdafx.h"

#include "Core/IO/DllLoader.h"

#include "Platform/Base/IRenderer.h"

#include "Core/Module/Module.h"
#include "Core/Graphics/GraphicsFactory.h"

namespace Core
{
	namespace Graphics
	{
		GraphicsModule::GraphicsModule(const char * moduleName)
		{
			m_dllLoader = new Core::DllLoader(moduleName);

			get = (Core::Graphics::detail::GetGraphicsFactory)m_dllLoader->getProcess(TO_STRING(base_GetGraphicsFactory));
			release = (Core::Graphics::detail::ReleaseGraphicsFactory)m_dllLoader->getProcess(TO_STRING(base_ReleaseGraphicsFactory));

			m_Factory = get();
		}

		GraphicsModule::~GraphicsModule()
		{
			release(&m_Factory);

			delete m_dllLoader;
		}

		void Core::Graphics::GraphicsModule::CreateRenderer(HWND hWnd, Platform::detail::IRenderer ** renderer)
		{
			m_Factory->create(hWnd, renderer);
		}

		void GraphicsModule::ReleaseRenderer(Platform::detail::IRenderer ** renderer)
		{
			m_Factory->release(renderer);
		}

	}// namespace Core::Graphics 
}//namespace Core