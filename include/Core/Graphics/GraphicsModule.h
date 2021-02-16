#pragma once
#ifndef CORE_GRAPHICSMODULE_H
#define CORE_GRAPHICSMODULE_H

namespace Core
{
	class DllLoader;

	namespace Graphics
	{

		/*
		* @brief DLL関数
		*/
		typedef ::Platform::Graphics::detail::IGraphics* (*GetGraphics)();
		EXTERN_C ENGINE_API::Platform::Graphics::detail::IGraphics* base_GetGraphics();

		typedef void(*ReleaseGraphics)(::Platform::Graphics::detail::IGraphics** instance);
		EXTERN_C ENGINE_API void base_ReleaseGraphics(::Platform::Graphics::detail::IGraphics** instance);


		/**
		* @class    GraphicsModule
		* @brief    グラフィック関連のモジュール
		*/
		class GraphicsModule : public ::Platform::detail::IModule
		{
		private:
			::Platform::IO::DllLoader* m_dllLoader;

			::Platform::Graphics::detail::IGraphics* m_Graphics;

			Core::Graphics::GetGraphics get;
			Core::Graphics::ReleaseGraphics release;

		public:
			GraphicsModule(const char* moduleName);
			virtual ~GraphicsModule();

			// Renderer
			void CreateRenderer(HWND hWnd, ::Platform::Graphics::detail::IRenderer** renderer);
			void ReleaseRenderer(::Platform::Graphics::detail::IRenderer** renderer);

		};// class GraphicsModule

	}// namespace Core::Graphics
}// namespace Core

#endif // ifndef CORE_GRAPHICSMODULE_H