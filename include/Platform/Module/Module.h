#pragma once
#ifndef PLATFORM_MODULE_H
#define PLATFORM_MODULE_H

namespace Platform
{
	namespace detail
	{
		/**
		* @class    IModule
		* @brief    Module���N���X
		*/
		class IModule
		{
		private:

		public:
			IModule() {};
			virtual ~IModule() {};
		};//class IModule

	}// namespace Platform::detail
}// namespace Platform

#endif// ifndef PLATFORM_MODULE_H