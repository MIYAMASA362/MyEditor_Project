#include"stdafx.h"

#include<string>
#include<Windows.h>


#include"Base/Logger.h"
#include"IO/PathHelper.h"

namespace Platform
{
	namespace detail
	{
		std::string PathFormat::getFileName(const std::string * path)
		{
			size_t begin = path->find_last_of(cDirectorySeparatorChar) + 1;
			size_t length = path->find_last_of('.') - begin;
			return path->substr(begin,length);
		}

		std::string PathFormat::getFileNameSub(const std::string * path)
		{
			return path->substr(path->find_last_of(cDirectorySeparatorChar) + 1);
		}

		std::string PathFormat::getFileExtension(const std::string * path)
		{
			return path->substr(path->find_last_of("."));
		}

		//In Development
		bool PathFormat::isRoot(std::string * path)
		{
			LOG_WARRNING("Use In Development function");

			//unix
			if(path->length() == 1 && path->c_str()[0] == '/')
			{
				return true;
			}

			//Windows
			if(path->c_str()[0] == ':')
			{
				
			}

			return false;
		}

	}//namespace Platform::detail
}//namespace Platform

