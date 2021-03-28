#pragma once
#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

namespace Core
{
	class Window
	{
		friend LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public:
		Window(
			IN HINSTANCE hInstance,
			IN LPSTR lpClassName,
			IN LPSTR lpCaption,
			IN int x,
			IN int y,
			IN long width,
			IN long height,
			IN DWORD style
		);
		virtual ~Window();

		HWND GetHWnd();

	private:
		LRESULT localWndProc(
			IN HWND hWnd, 
			IN UINT uMsg,
			IN WPARAM wParam,
			IN LPARAM lParam
		);
		
		HWND m_hWnd;

	};// class Window
}// namespace Core

#endif // ifndef CORE_WINDOW_H