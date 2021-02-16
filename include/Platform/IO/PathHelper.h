#pragma once
#ifndef PLATFORM_PATHHELPER_H
#define PLATFORM_PATHHELPER_H

namespace Platform
{
	namespace IO
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
	}// namespace Platform::IO
}//namespace Platform

#endif //ifndef PLATFORM_PATHHELPER_H