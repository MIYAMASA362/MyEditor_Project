#include<string>

#include "Platform/Config.h"
#include "PathHelper.h"
#include "Core/IO/Path.h"

namespace Core
{
	Path::Path()
	{

	}

	Path::Path(const char * path)
		:
		m_path(path)
	{

	}

	Path::Path(const std::string & path)
		:
		m_path(path)
	{

	}

	Path::~Path()
	{

	}

	bool Path::isEnmpty() const
	{
		return m_path.empty();
	}

	int Path::lenght() const
	{
		return m_path.length();
	}

	const char * Path::c_str() const
	{
		return m_path.c_str();
	}

	const std::string & Path::str() const
	{
		return m_path;
	}

	std::string Path::getFileName() const
	{
		size_t begin = m_path.find_last_of("\\") + 1;
		size_t end = m_path.find_last_of(".") - begin;
		return m_path.substr(begin,end);
	}

	std::string Path::getFile() const
	{
		return m_path.substr(m_path.find_last_of("\\") + 1);
	}

	std::string Path::getExtension() const
	{
		return m_path.substr(m_path.find_last_of("."));
	}

}//namespace Core