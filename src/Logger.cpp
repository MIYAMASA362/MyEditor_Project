#include"Logger.h"

#if !defined(DISABLE_LOGGING)

Log::Logger::Logger(LogLevel::Severity severity)
	:
	m_Severity(severity)
{

}

Log::Logger::~Logger()
{

}

#endif