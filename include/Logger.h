/*
*	one log output need 1KiB buffer size
*
*
*
*/
#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include"Common.h"

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

namespace Log
{
	/**
	*	@brief 出力ログに対する表示
	*/
	static inline int OutputPrint(const char* fmt,...)
	{
		char buffer[512] = { '\0' };
		va_list args;
		va_start(args,fmt);
		LOGGER_VSPRINTF(buffer,sizeof(buffer),fmt,args);
		va_end(args);
		LOGGER_OUTPUT(buffer);
		return 1;
	}

	/**
	*	@brief ログの通知レベル
	*/
	class LogLevel
	{
	public:
		enum Severity
		{
			Unkown,
			Debug,
			Info,
			Warning,
			Error,
			Fatal
		};

		static inline std::string ToString(LogLevel::Severity severity)
		{
			switch (severity)
			{
			case Log::LogLevel::Debug:		return "Debug";
			case Log::LogLevel::Info:		return "Info";
			case Log::LogLevel::Warning:	return "Warning";
			case Log::LogLevel::Error:		return "Error";
			case Log::LogLevel::Fatal:		return "Fatal";
			default: return "UnKown";
			}
		};

	};// class LogLevel

	/**
	* @class    Logger
	* @brief    
	*/
	class ENGINE_API Logger final
	{
	private:
		Logger(const Logger&) = delete;
		Logger& operator=(Logger&) = delete;

		LogLevel::Severity m_Severity;

	public:
		EXPLICIT Logger(LogLevel::Severity severity);
		~Logger();
	
		static inline void Write(const LogLevel::Severity& severity,const char* fmt,...)
		{
			char buffer[512] = { '\0' };
			va_list args;
			va_start(args, fmt);
			LOGGER_VSPRINTF(buffer, sizeof(buffer), fmt, args);
			va_end(args);

			OutputPrint(
				"Logger LogLevel : %s \n"
				"Message : %s\n"
				"Func : %s\n"
				"file :%s, line :%d\n",
					LogLevel::ToString(severity).c_str(),
					buffer,
					FUNCTION,
					__FILE__,
					__LINE__
				);
		}

		// debug
		template<typename... Args>
		static inline void LogDebug(const char* fmt,Args... args)
		{
			Write(LogLevel::Debug,fmt,std::forward<Args>(args)...);
		}

		// info
		template<typename... Args>
		static inline void LogInfo(const char* fmt,Args... args)
		{
			Write(LogLevel::Info,fmt,std::forward<Args>(args)...);
		}

		// warning
		template<typename... Args>
		static inline void LogWarning(const char* fmt,Args... args)
		{
			Write(LogLevel::Warning,fmt,std::forward<Args>(args)...);
		}

		// error
		template<typename... Args>
		static inline void LogError(const char* fmt,Args... args)
		{
			Write(LogLevel::Error,fmt,std::forward<Args>(args)...);
		}

		// fatal
		template<typename... Args>
		static inline void LogFatal(const char* fmt,Args... args)
		{
			Write(LogLevel::Fatal,fmt,std::forward<Args>(args)...);
		}

	};// class Logger

}// namespace Log

#define LOG_DEBUG(format,...)		Log::Logger::LogDebug(format,__VA_ARGS__);
#define LOG_INFO(format,...)		Log::Logger::LogInfo(format,__VA_ARGS__);
#define LOG_WARRNING(format,...)	Log::Logger::LogWarning(format,__VA_ARGS__);
#define LOG_ERROR(format,...)		Log::Logger::LogError(format,__VA_ARGS__);
#define LOG_FATAL(format,...)		Log::Logger::LogFatal(format,__VA_ARGS__);

#else // if !defined(DISABLE_LOGGING)

#define LOG_DEBUG(format,...)
#define LOG_INFO(format,...)
#define LOG_WARRNING(format,...)
#define LOG_ERROR(format,...)
#define LOG_FATAL(format,...)

#endif // defined(DISABLE_LOGGING)

#endif // ifndef LOGGER_H
