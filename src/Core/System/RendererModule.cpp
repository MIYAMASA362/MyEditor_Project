#include"Config.h"

#include"Platform/IO/DllLoader.h"
#include"Platform/Base/Result.h"

#include"Platform/Base/IRenderer.h"

#include"Core/System/IModule.h"
#include"Core/System/RendererModule.h"

using namespace Platform::detail;

namespace Core
{
	RendererModule::RendererModule(const char* moduleName)
	:
		IModule(moduleName)
	{

	}

	RendererModule::~RendererModule()
	{
		
	}

	Result RendererModule::CreateRendererDevice(OUT Platform::IRendererDevice** output)
	{
		GetIRendererDevice get = nullptr;
		get = (GetIRendererDevice)m_dllLoader->getProcess(TO_STRING(getIRendererDevice));

		if (get == nullptr) return Result(false);

		Platform::IRendererDevice* result = nullptr;
		result = get();
		if (result == nullptr) return Result(false);

		(*output) = result;

		return Result(true);
	}

}// namespace Core