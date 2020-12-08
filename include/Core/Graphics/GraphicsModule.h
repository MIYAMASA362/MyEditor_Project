#pragma once
#ifndef CORE_GRAPHICSMODULE_H
#define CORE_GRAPHICSMODULE_H

namespace Core
{
	class DllLoader;

	namespace Graphics
	{
		class IGraphicsFactory;

		/*
		* @brief DLL関数
		*/
		namespace detail
		{
			typedef IGraphicsFactory* (*GetGraphicsFactory)();
			EXTERN_C ENGINE_API IGraphicsFactory* base_GetGraphicsFactory();

			typedef void(*ReleaseGraphicsFactory)(IGraphicsFactory** instance);
			EXTERN_C ENGINE_API void base_ReleaseGraphicsFactory(IGraphicsFactory** instance);

		}// namespace Core::detail

		/**
		* @class    GraphicsModule
		* @brief    グラフィック関連のモジュール
		*/
		class GraphicsModule : public ::Platform::detail::IModule
		{
		private:
			::Platform::DllLoader* m_dllLoader;

			IGraphicsFactory* m_Factory;

			Core::Graphics::detail::GetGraphicsFactory get;
			Core::Graphics::detail::ReleaseGraphicsFactory release;

		public:
			GraphicsModule(const char* moduleName);
			virtual ~GraphicsModule();

			void CreateRenderer(HWND hWnd, ::Platform::Graphics::detail::IRenderer** renderer);
			void ReleaseRenderer(::Platform::Graphics::detail::IRenderer** renderer);

		};// class GraphicsModule

	}// namespace Core::Graphics
}// namespace Core

#endif // ifndef CORE_GRAPHICSMODULE_H