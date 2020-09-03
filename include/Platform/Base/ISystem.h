#pragma once
#ifndef PLATFORM_ISYSTEM_H
#define PLATFORM_ISYSTEM_H

namespace Platform
{
	namespace detail
	{
		/**
		* @class    ISystem
		* @brief    �G���W���̊�V�X�e����Intarface
		*/
		class ENGINE_API ISystem
		{
		private:
			

		public:
			ISystem() = default;
			virtual ~ISystem() = default;

			virtual int mainLoop() = 0;

		};//class ISystem

	}//namespace Platform::detail
}//namespace Platform

#endif //ifndef PLATFORM_ISYSTEM_H