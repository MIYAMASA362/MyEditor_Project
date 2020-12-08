#include"stdafx.h"

#include"Base/Logger.h"

#if !defined(DISABLE_LOGGING)

namespace Platform
{

	Logger::Logger(detail::LogLevel::Severity severity)
		:
		m_Severity(severity)
	{

	}

	Logger::~Logger()
	{

	}

}// namespace Platform

#endif // ifndef !defined(DISABLE_LOGGING)