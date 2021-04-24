#pragma once
#ifndef CORE_RENDERERMODULE_H
#define CORE_RENDERERMODULE_H

namespace Core
{
	class RendererModule : public IModule
	{
	public:
		RendererModule(const char* moduleName);
		virtual ~RendererModule();

		virtual Result CreateRendererDevice(OUT Platform::IRendererDevice**);

	};// class RendererModule

}// namespace Core

#endif // ifndef CORE_RENDERERMODULE_H