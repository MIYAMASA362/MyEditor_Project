#include "stdafx.h"

#include<string>

#include "Core/IO/PathHelper.h"
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
		return Core::detail::PathFormat::getFileName(&m_path);
	}

	std::string Path::getFile() const
	{
		return Core::detail::PathFormat::getFileNameSub(&m_path);
	}

	std::string Path::getExtension() const
	{
		return Core::detail::PathFormat::getFileExtension(&m_path);
	}

}//namespace Core