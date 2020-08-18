#pragma once
#ifndef ISYSTEM_H
#define ISYSTEM_H

namespace Platform
{
	namespace detail
	{
		/**
		* @class    ISystem
		* @brief    Platform層が提供するシステムの基盤
		*/
		class ISystem
		{
		private:

		public:
			ISystem() {};
			virtual ~ISystem() {};

			virtual void Initialize() = 0;
			virtual void Update() = 0;
			virtual void Finalize() = 0;

		};//class ISystem

	}//namespace Platform::detail
}//namespace Platform

#endif //ifndef ISYSTEM_H