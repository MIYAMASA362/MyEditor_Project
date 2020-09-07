#pragma once
#ifndef CORE_IO_PATHHELPER_H
#define CORE_IO_PATHHELPER_H

namespace Core
{
	namespace detail
	{
		class PathFormat
		{
		private:
#ifdef ENGINE_WIN
			static const char cDirectorySeparatorChar = '\\';
#else //other
			static const char cDirectorySeparatorChar = 0x00;
#endif

		public:
			static std::string getFileName(const std::string* path);
			static std::string getFileNameSub(const std::string* path);
			static std::string getFileExtension(const std::string* path);

			static bool isRoot(std::string* path);

		};//class PathFormat

	}//namespace detail
}//namespace Core

#endif //ifndef CORE_IO_PATHHELPER_H