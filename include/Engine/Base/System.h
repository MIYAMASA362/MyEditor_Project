#pragma once
#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

namespace Engine
{
	/**
	* @class    RenderingDirector
	* @brief    •`‰æˆ—‚Ì“®ì‚ğó‚¯‚Â
	*/
	class RenderingDirector
	{
	public:
		RenderingDirector() = default;
		virtual ~RenderingDirector() = default;

		virtual void ProcessLoop() = 0;

	private:

	};// class RenderingDirector
	
	class EngineDevice
	{
	public:
		EngineDevice(
			IN HINSTANCE hInstance,
			IN LPSTR lpClassName,
			IN LPSTR lpCaption,
			IN int x,
			IN int y,
			IN long width,
			IN long height,
			IN DWORD style
		);
		virtual ~EngineDevice();

		int ProcessLoop();
		virtual void Release();

	private:
		Core::Window m_window;
		
	};// class EngineDevice

}//namespace Engine

#endif //ifndef ENGINE_H