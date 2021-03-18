#pragma once
#ifndef PLATFORM_ISYSTEM_H
#define PLATFORM_ISYSTEM_H

namespace Platform
{
	namespace detail
	{
		/**
		* @class    ISystem
		* @brief    エンジンの基幹システムのIntarface
		*/
		class ISystem
		{
		public:
			ISystem() ENGINE_DEFAULT;
			virtual ~ISystem() ENGINE_DEFAULT;

			virtual int mainLoop() ENGINE_PURE;

		};//class ISystem

	}//namespace Platform::detail
}//namespace Platform

#endif //ifndef PLATFORM_ISYSTEM_H