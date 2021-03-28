#include"Config.h"

#include"Base/Result.h"
#include"Base/IRenderer.h"

#include"IO/DllLoader.h"

namespace Platform
{
	IRenderer::IRenderer()
	{

	}

	IRenderer::~IRenderer()
	{
	}

	Result CreateRenderer(IN RENDERER_DESC* desc, OUT IRenderer** output)
	{
		IO::DllLoader dllLoader(desc->moduleName);

		detail::GetIRenderer get = (detail::GetIRenderer)dllLoader.getProcess(TO_STRING(detail::getIRenderer));

		IRenderer* result = nullptr;

		result = get(desc);

		if (result == nullptr) return Result(false);

		(*output) = result;

		return Result(true);
	}

}// namespace Platform