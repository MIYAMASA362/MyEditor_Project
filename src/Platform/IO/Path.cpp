#include "Config.h"

#include<string>

#include "IO/PathHelper.h"
#include "IO/Path.h"

namespace Platform
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

	size_t Path::lenght() const
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
		return detail::PathFormat::getFileName(&m_path);
	}

	std::string Path::getFile() const
	{
		return detail::PathFormat::getFileNameSub(&m_path);
	}

	std::string Path::getExtension() const
	{
		return detail::PathFormat::getFileExtension(&m_path);
	}

}//namespace Platform