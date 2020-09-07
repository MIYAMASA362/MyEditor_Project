#pragma once
#ifndef CORE_IO_DLLLOADER_H
#define CORE_IO_DLLLOADER_H

namespace Core
{
	/**
	* @class    DllLoader
	* @brief    
	*/
	class DllLoader final
	{
	private:
		HMODULE m_hModule;

	public:
		DllLoader();
		DllLoader(const char* libfileName);
		~DllLoader();

		bool load(const char* libfileName);
		void free();

		FARPROC getProcess(const char* funcName);

	};//class DllLoader

}//namespace Core

#endif //CORE_IO_DLLLOADER_H