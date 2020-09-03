/*
*	one log output need 1KiB buffer size
*
*
*
*/
#pragma once

#ifndef LOGGER_H
#define LOGGER_H

// Logger Macro
#define LOGGER_OUTPUT(text) OutputDebugStringA(text);

// FUNCTION Macro
#ifdef _WIN32
#define FUNCTION __FUNCTION__
#define LOGGER_VSPRINTF(buffer,length,format,arg) _vsnprintf_s(buffer,length,format,arg)

#else
#define FUNCTION __func__
#define LOGGER_VSPRINTF(buffer,length,format,arg) _vsnprintf_s(buffer,length,format,arg)

#endif

#if !defined(DISABLE_LOGGING)

namespace Core
{
	namespace detail
	{

		/**
		*	@brief 出力ログに対する表示
		*/
		static inline int OutputPrint(const char* fmt, ...)
		{
			char buffer[512] = { '\0' };
			va_list args;
			va_start(args, fmt);
			LOGGER_VSPRINTF(buffer, sizeof(buffer), fmt, args);
			va_end(args);
			LOGGER_OUTPUT(buffer);
			return 1;
		}

		/**
		*	@brief ログの通知レベル
		*/
		class LogLevel final
		{
		public:
			enum Severity
			{
				Unkown,
				Debug,
				Info,
				Warning,
				Error,
				Fatal,
				Assert
			};

			static inline std::string ToString(LogLevel::Severity severity)
			{
				switch (severity)
				{
				case LogLevel::Debug:		return "Debug";
				case LogLevel::Info:		return "Info";
				case LogLevel::Warning:		return "Warning";
				case LogLevel::Error:		return "Error";
				case LogLevel::Fatal:		return "Fatal";
				case LogLevel::Assert:		return "Assert";
				default: return "Unkown";
				}
			};

		};// class LogLevel

	}//namespace log::detail

	/**
	* @class    Logger
	* @brief    
	*/
	class Logger final
	{
	private:
		Logger(const Logger&) = delete;
		Logger& operator=(Logger&) = delete;

		detail::LogLevel::Severity m_Severity;

	public:
		EXPLICIT Logger(detail::LogLevel::Severity severity);
		~Logger();
	
		static inline void Write(const detail::LogLevel::Severity& severity, const char* funcName, const char* fileName, const int lineNum, const char* fmt, ...)
		{
			char buffer[512] = { '\0' };
			va_list args;
			va_start(args, fmt);
			LOGGER_VSPRINTF(buffer, sizeof(buffer), fmt, args);
			va_end(args);

			detail::OutputPrint(
				"Logger LogLevel : %s ("
				"Message : %s)\n"
				"Func : %s"
				"(file :%s, line :%d)\n",
					detail::LogLevel::ToString(severity).c_str(),
					buffer,
					funcName,
					fileName,
					lineNum
				);
		}

		// debug
		template<typename... Args>
		static inline void LogDebug(const char* fmt,const char* funcName,const char* fileName,const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Debug,funcName,fileName,lineNum,fmt,std::forward<Args>(args)...);
		}

		// info
		template<typename... Args>
		static inline void LogInfo(const char* fmt,const char* funcName,const char* fileName,const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Info,funcName,fileName,lineNum,fmt,std::forward<Args>(args)...);
		}

		// warning
		template<typename... Args>
		static inline void LogWarning(const char* fmt,const char* funcName,const char* fileName,const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Warning,funcName,fileName,lineNum,fmt,std::forward<Args>(args)...);
		}

		// error
		template<typename... Args>
		static inline void LogError(const char* fmt,const char* funcName,const char* fileName,const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Error,funcName,fileName,lineNum,fmt,std::forward<Args>(args)...);
		}

		// fatal
		template<typename... Args>
		static inline void LogFatal(const char* fmt,const char* funcName,const char* fileName,const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Fatal,funcName,fileName,lineNum,fmt,std::forward<Args>(args)...);
		}

		// assert
		template<typename... Args>
		static inline void LogAssert(const char* fmt, const char* funcName, const char* fileName, const int lineNum, Args... args)
		{
			Write(detail::LogLevel::Assert, funcName, fileName, lineNum, fmt, std::forward<Args>(args)...);
		}

	};// class Logger

}// namespace log

#define LOG_DEBUG(format,...)		Core::Logger::LogDebug(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);
#define LOG_INFO(format,...)		Core::Logger::LogInfo(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);
#define LOG_WARRNING(format,...)	Core::Logger::LogWarning(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);
#define LOG_ERROR(format,...)		Core::Logger::LogError(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);
#define LOG_FATAL(format,...)		Core::Logger::LogFatal(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);
#define LOG_ASSERT(format,...)		Core::Logger::LogAssert(format,FUNCTION,__FILE__,__LINE__,__VA_ARGS__);

#else // if !defined(DISABLE_LOGGING)

#define LOG_DEBUG(format,...)
#define LOG_INFO(format,...)
#define LOG_WARRNING(format,...)
#define LOG_ERROR(format,...)
#define LOG_FATAL(format,...)
#define LOG_ASSERT(format,...)


#endif // defined(DISABLE_LOGGING)

#endif // ifndef LOGGER_H
