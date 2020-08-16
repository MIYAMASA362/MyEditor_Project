#include"Core/Common.h"
#include"Core/Base/Logger.h"

#if !defined(DISABLE_LOGGING)

namespace Core {

	Logger::Logger(detail::LogLevel::Severity severity)
		:
		m_Severity(severity)
	{

	}

	Logger::~Logger()
	{

	}
}// namespace Core
#endif