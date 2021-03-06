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
		class ENGINE_API IWindow
		{
		protected:
			

		public:
			IWindow() = default;
			virtual ~IWindow() = default;

		};//class IWindow

	}//namespce Platform::detail
}//namespce Platform

#endif //ifndef PLATFORM_IWINDOW_H