#pragma once
#ifndef CORE_PATHHELPER_H
#define CORE_PATHHELPER_H

namespace Core
{
	namespace detail
	{
		class PathFormat
		{
		private:
#ifdef ENGINE_WIN
			static const char DirectorySeparatorChar = '\\';
#else //other
			static const char DirectorySeparatorChar = 0x00;
#endif

		public:
			static std::string getFileName(std::string* path);
			static std::string getFileNameSub(std::string* path);
			static std::string getFileExtension(std::string* path);

			static bool isRoot(std::string* path);

		};//class PathFormat

	}//namespace detail
}//namespace Core

#endif