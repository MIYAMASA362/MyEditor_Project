#include"stdafx.h"

#include<Windows.h>

#include"Core/Base/Result.h"
#include"Core/IO/DllLoader.h"

typedef int(WINAPI *MessageBoxFunc)(HWND,LPCWSTR,LPCWSTR,UINT);

namespace Core
{
	DllLoader::DllLoader()
		:
		m_hModule(NULL)
	{
		
	}

	DllLoader::DllLoader(const char * libfileName)
	{
		this->load(libfileName);
	}

	DllLoader::~DllLoader()
	{
		if (m_hModule)
		{
			FreeLibrary(m_hModule);
		}
	}

	bool DllLoader::load(const char * libfileName)
	{
		m_hModule = LoadLibrary(libfileName);
		return m_hModule != NULL;
	}

	void DllLoader::free()
	{
		FreeLibrary(m_hModule);
	}

	FARPROC DllLoader::getProcess(const char * funcName)
	{
		return GetProcAddress(m_hModule,funcName);
	}

}//namespace Core