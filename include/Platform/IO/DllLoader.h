#pragma once
#ifndef PLATFORM_DLLLOADER_H
#define PLATFORM_DLLLOADER_H

namespace Platform
{
	namespace IO
	{

		/**
		* @class    DllLoader
		* @brief
		*/
		class DllLoader
		{
		private:
			HMODULE m_hModule;

		public:
			DllLoader();
			DllLoader(const char* libfileName);
			virtual ~DllLoader();

			bool load(const char* libfileName);
			void free();

			FARPROC getProcess(const char* funcName);

		};//class DllLoader

	}// namespace Platform::IO
}//namespace Platform

#endif //CORE_IO_DLLLOADER_H