#pragma once
#ifndef RESULT_H
#define RESULT_H

namespace Core
{
	namespace detail
	{
		enum class ResultLevel
		{
			Fail,
			Success,
		};//enum class ResultLevel

	}//namespace result::detail

}// namespace result

/**
* @class    Result
* @brief    
*/
class Result 
{
private:
	Core::detail::ResultLevel m_Level;

public:
	Result(bool result)
		:
		m_Level(result ? Core::detail::ResultLevel::Success : Core::detail::ResultLevel::Fail )
	{};

	Result(Core::detail::ResultLevel& resultlevel)
		:
		m_Level(resultlevel)
	{}

	Result& operator=(const Result& other)
	{
		m_Level = other.m_Level;
		return *this;
	}

	operator bool() const { return m_Level != Core::detail::ResultLevel::Fail; }

};// class Result

#endif //ifndef RESULT_H
