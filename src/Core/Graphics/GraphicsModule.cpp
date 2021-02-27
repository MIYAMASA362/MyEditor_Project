#include"Config.h"

#include"Core/Graphics/GraphicsModule.h"

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
	}
}
