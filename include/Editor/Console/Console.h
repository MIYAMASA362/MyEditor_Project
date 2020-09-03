#pragma once
#ifndef EDITOR_CONSOLE
#define EDITOR_CONSOLE

namespace Editor
{
	namespace detail
	{
		/**
		* @class    Console
		* @brief    Enum Description
		*/
		class Console final
		{
		private:
			HANDLE m_hOutput;
			CONSOLE_SCREEN_BUFFER_INFO m_ScreenBuf;

		public:
			Console();
			~Console();



			void create();
			void close();

		};//class Console
	
	}//namespace detail
}//namespace Eidtor

#endif //ifndef EDITOR_CONSOLE