#include"Config.h"

#include"IO/DllLoader.h"

namespace Platform
{
	namespace IO
	{
		DllLoader::DllLoader()
			:
			m_hModule(NULL)
		{

		}

		DllLoader::DllLoader(const char* libfileName)
		{
			this->load(libfileName);
		}

		DllLoader::~DllLoader()
		{
			if (m_hModule)
			{
				this->free();
			}
		}

		bool DllLoader::load(const char* libfileName)
		{
			m_hModule = LoadLibrary(libfileName);
			return m_hModule != NULL;
		}

		void DllLoader::free()
		{
			FreeLibrary(m_hModule);
		}

		FARPROC DllLoader::getProcess(const char* funcName)
		{
			return GetProcAddress(m_hModule, funcName);
		}

	}// namespace Platform::IO
}//namespace Platform