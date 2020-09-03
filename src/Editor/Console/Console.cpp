#include<Windows.h>
#include<io.h>
#include<fcntl.h>
#include"Platform/Config.h"
#include"Editor/Console/Console.h"

namespace Editor
{
	namespace detail
	{
		Console::Console()
		{

		}

		Console::~Console()
		{
		}

		void Console::create()
		{
#if defined(ENGINE_WIN)
			//Add a new Console Window in Application
			AllocConsole();

			m_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(m_hOutput,&m_ScreenBuf);

			WriteConsole(m_hOutput,"Console Open",13,NULL,NULL);
#endif
		}

		void Console::close()
		{
#if defined(ENGINE_WIN)
			FreeConsole();
#endif
		}

	}//namespace detail
}//namespace Editor