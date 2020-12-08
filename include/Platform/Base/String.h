#pragma once
#ifndef PLATFORM_STRING_H
#define PLATFORM_STRING_H

namespace Platform
{
	/**
	* @class    String
	* @brief    Enum Description
	*/
	class String final
	{
	private:
		size_t m_capacity;
		size_t m_size;
		char* m_data;

	public:
		String();
		String(const size_t n,const char c);
		String(const char* c);
		String(const char* front,const char* length);
		String(const String& s);

		~String();

		const char& operator[](const size_t n) const;
		char& operator[](const size_t n);
		String operator+(const char* c);
		String operator+(const String& str);
		String& operator+=(const char* c);
		String& operator+=(const String& str);
		bool operator==(const char* c);

		bool empty() const;
		size_t size() const;
		size_t length() const;
		size_t capacity() const;
		char& front() const;
		char& back() const;
		String substr(const size_t index,const size_t size) const;
		const char* c_str() const;
		const char* data() const;
		size_t find(const char* c,const size_t index) const;



	};//class CString


}//namespace Platform

#endif //ifndef CORE_STRING_H