#pragma once
#ifndef PLATFORM_IRENDERER_H
#define PLATFORM_IRENDERER_H

namespace Platform
{
	struct RENDERER_DESC
	{
		char* moduleName;
		HWND hWnd;
	};

	class IRenderer;

	class IRendererDevice
	{
	public:
		IRendererDevice();
		virtual ~IRendererDevice();

		virtual Result CreateRenderer(IRenderer**);

		virtual void Release() ENGINE_PURE;
	};

	class IRenderer
	{
	public:
		IRenderer();
		virtual ~IRenderer();

		virtual void Clear() ENGINE_PURE;
		virtual void Begin() ENGINE_PURE;
		virtual void End() ENGINE_PURE;

		virtual void Release() ENGINE_PURE;

	private:


	};// class IRenderer

	Result CreateRendererDevice(
		IN const char*,
		OUT IRendererDevice**
	);

	Result CreateRenderer(
		IN RENDERER_DESC* desc,
		OUT IRenderer** output
	);

	namespace detail
	{
		typedef IRenderer* (*GetIRenderer)(RENDERER_DESC* desc);
		EXTERN_C ENGINE_API IRenderer* getIRenderer();
	}

}// namespace Platform

#endif // ifndef PLATFORM_IRENDERER_H