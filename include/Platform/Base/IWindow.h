#pragma once
#ifndef PLATFORM_IWINDOW_H
#define PLATFORM_IWINDOW_H

namespace Platform
{
	namespace detail
	{
		/**
		* @class    IWindow
		* @brief    Paltform層が提供するウィンドウの基盤
		*/
		class IWindow
		{
		protected:
			ISystem* m_System;

		public:
			IWindow(ISystem* main);
			virtual ~IWindow();

			virtual int messageLoop() = 0;

		};//class IWindow

	}//namespce Platform::detail
}//namespce Platform

#endif //ifndef PLATFORM_WINDOW_H