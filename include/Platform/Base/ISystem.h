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
		class ISystem
		{
		private:
			

		public:
			ISystem() {};
			virtual ~ISystem() {};

			virtual int mainLoop() = 0;

		};//class ISystem

	}//namespace Platform::detail
}//namespace Platform

#endif //ifndef PLATFORM_ISYSTEM_H