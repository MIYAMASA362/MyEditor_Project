#pragma once
#ifndef PLATFORM_IWINDOW_H
#define PLATFORM_IWINDOW_H

namespace Platform
{
	namespace detail
	{	
		/**
		* @class    IWindow
		* @brief    �G���W�������p����E�B���h�E��Interface
		*/
		class ENGINE_API IWindow
		{
		protected:
			

		public:
			IWindow() ENGINE_DEFAULT;
			virtual ~IWindow() ENGINE_DEFAULT;

		};//class IWindow

	}//namespce Platform::detail
}//namespce Platform

#endif //ifndef PLATFORM_IWINDOW_H