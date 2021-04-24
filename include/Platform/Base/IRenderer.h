#pragma once
#ifndef PLATFORM_IRENDERER_H
#define PLATFORM_IRENDERER_H

namespace Platform
{
	namespace IO
	{
		class DllLoader;
	}
}

namespace Platform
{
	struct RENDERER_DESC
	{
		char* moduleName;
		HWND hWnd;
	};

	/**
	* @class    IRenderer
	* @brief
	*/
	class IRenderer
	{
	public:
		virtual void Clear() ENGINE_PURE;
		virtual void Begin() ENGINE_PURE;
		virtual void End() ENGINE_PURE;
		virtual void Release() ENGINE_PURE;

	protected:
		IRenderer();
		virtual ~IRenderer();

	};// class IRenderer

	/**
	* @class    IRendererDevice
	* @brief    ï`âÊã§í ê›íË
	*/
	class IRendererDevice
	{
	public:
		virtual Result CreateRenderer(HWND, IRenderer**) ENGINE_PURE;
		virtual void Release() ENGINE_PURE;

	protected:
		IRendererDevice();
		virtual ~IRendererDevice();

	};// class IRendererDevice

	// Dll
	namespace detail
	{
		typedef IRendererDevice* (*GetIRendererDevice)();
		EXTERN_C ENGINE_API IRendererDevice* getIRendererDevice();
	}

}// namespace Platform

#endif // ifndef PLATFORM_IRENDERER_H