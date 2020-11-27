#pragma once
#ifndef CORE_GRAPHICSFACTOR_H
#define CORE_GRAPHICSFACTOR_H

namespace Core
{
	class DllLoader;

	/**
	* @class    IGraphicsFactory
	* @brief
	*/
	class ENGINE_API IGraphicsFactory
	{
		//static_assert(std::is_base_of<Platform::detail::IRenderer,Type>::value,"Type must inherit form IRenderer");
	public:
		using Value_Type = ::Platform::detail::IRenderer;

		IGraphicsFactory() {};
		virtual ~IGraphicsFactory() {};

	public:
		virtual void create(HWND hWnd, Value_Type** output) = 0;
		virtual void release(Value_Type** instance) = 0;

	};//class IGraphicsFactory

	/*
	* @brief DLL関数
	*/
	namespace detail
	{
		typedef IGraphicsFactory* (*GetGraphicsFactory)();
		extern "C" ENGINE_API IGraphicsFactory* base_GetGraphicsFactory();

		typedef void(*ReleaseGraphicsFactory)(IGraphicsFactory** instance);
		extern "C" ENGINE_API void base_ReleaseGraphicsFactory(IGraphicsFactory** instance);

	}// namespace Core::detail

	/**
	* @class    GraphicsModule
	* @brief    グラフィック関連のモジュール
	*/
	class GraphicsModule : public ::Core::detail::IModule
	{
	private:
		Core::DllLoader* m_dllLoader;

		IGraphicsFactory* m_Factory;

		Core::detail::GetGraphicsFactory get;
		Core::detail::ReleaseGraphicsFactory release;

	public:
		GraphicsModule(const char* moduleName);
		virtual ~GraphicsModule();

		void CreateRenderer(HWND hWnd, ::Platform::detail::IRenderer** renderer);
		void ReleaseRenderer(::Platform::detail::IRenderer** renderer);

	};// class GraphicsModule

}// namespace Core

#endif //ifndef CORE_GRAPHICSFACTORY_H