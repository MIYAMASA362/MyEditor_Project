#pragma once
#ifndef CORE_MODULE_H
#define CORE_MODULE_H

namespace Core
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

	}// namespace Core::detail
}// namespace Core

#endif// ifndef CORE_MODULE_H