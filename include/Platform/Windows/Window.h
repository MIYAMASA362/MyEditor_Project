#pragma once
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

namespace Platform
{
	namespace Windows
	{
		/**
		* @class    Window Windows32
		* @brief	Windows Platform version
		*/
		class ENGINE_API Window : public detail::IWindow
		{
		protected:
			HWND m_hWnd;

		public:
			Window();
			virtual ~Window();

			virtual LRESULT localWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
			virtual HRESULT Create(HINSTANCE hInstance, LPSTR lpClassName, LPSTR lpCaption, int x, int y, long width, long height, DWORD style);

			void SetProcParam(HWND hWnd);
			HWND GetHWnd() { return m_hWnd; };

		};//class Window

	}//namespace Platform::Windows
}//namespce Platform

#endif//ifndef WINDOWS_WINDOW_H