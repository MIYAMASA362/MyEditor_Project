#pragma once
#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

namespace Engine
{
	/**
	* @class    System
	* @brief	アプリケーションの基幹システム
	*/
	class System final : public Core::System::ISystem
	{
	private:
		
	public:
		// 
		::Platform::Graphics::detail::IRenderer* m_Renderer;

	public:

		System();
		virtual ~System();

		virtual int mainLoop() override;

	};//class System

	class EngineDevice
	{
	public:
		EngineDevice();
		virtual ~EngineDevice();

		int ProcessLoop();
		virtual void Release();

	private:
		
	};// class EngineDevice

#ifdef ENGINE_WIN
	Result CreateEngine(
		IN HINSTANCE hInstance,
		IN LPSTR lpClassName,
		IN LPSTR lpCaption,
		IN int x, 
		IN int y,
		IN long width,
		IN long height,
		IN DWORD style,
		OUT EngineDevice**
	);
#else
	/*static Result CreateEngine(
		OUT EngineCore**
	);*/
#endif

}//namespace Engine

#endif //ifndef ENGINE_H