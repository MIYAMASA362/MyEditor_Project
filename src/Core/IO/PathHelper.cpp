#include<string>
#include"Core/IO/PathHelper.h"

namespace Core
{
	namespace detail
	{
		std::string PathFormat::getFileName(std::string * path)
		{
			return std::string();
		}

		std::string PathFormat::getFileNameSub(std::string * path)
		{
			return std::string();
		}

		std::string PathFormat::getFileExtension(std::string * path)
		{
			return std::string();
		}

		bool PathFormat::isRoot(std::string * path)
		{
			return false;
		}

	}//namespace detail
}//namespace Core

