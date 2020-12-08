#pragma once
#ifndef PLATFORM_RESULT_H
#define PLATFORM_RESULT_H

namespace Platform
{
	namespace detail
	{
		enum class ResultLevel
		{
			Fail,
			Success,
		};//enum class ResultLevel

	}//namespace Platform::detail

}// namespace Platform

namespace Platform
{
	/**
	* @class    Result
	* @brief
	*/
	class Result
	{
	private:
		detail::ResultLevel m_Level;

	public:
		Result(bool result)
			:
			m_Level(result ? detail::ResultLevel::Success : detail::ResultLevel::Fail)
		{};

		Result(detail::ResultLevel& resultlevel)
			:
			m_Level(resultlevel)
		{}

		Result& operator=(const Result& other)
		{
			m_Level = other.m_Level;
			return *this;
		}

		operator bool() const { return m_Level != detail::ResultLevel::Fail; }

	};// class Result

}// namespace Platform

typedef ::Platform::Result Result;

#endif //ifndef PLATFORM_RESULT_H
