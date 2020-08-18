#pragma once
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

namespace Platform
{
	namespace Windows
	{
		/**
		* @class    Window Windows32
		* @brief	Windows
		*/
		class Window : public detail::IWindow
		{
		protected:
			HWND m_hWnd;

		public:
			Window(detail::ISystem* main);
			virtual ~Window();

			virtual int messageLoop() override;

		};//class Window

	}//namespace Platform::Windows
}//namespce Platform

#endif//ifndef WINDOWS_WINDOW_H