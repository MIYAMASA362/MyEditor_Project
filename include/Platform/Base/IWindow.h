#pragma once
#ifndef PLATFORM_IWINDOW_H
#define PLATFORM_IWINDOW_H

namespace Platform
{
	namespace detail
	{	
		/**
		* @class    IWindow
		* @brief    エンジンが利用するウィンドウのInterface
		*/
		class IWindow
		{
		protected:
			

		public:
			IWindow(){};
			virtual ~IWindow() {};

		};//class IWindow

	}//namespce Platform::detail
}//namespce Platform

#endif //ifndef PLATFORM_IWINDOW_H