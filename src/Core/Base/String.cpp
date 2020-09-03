#include"stdafx.h"

#include"Core/Base/String.h"

/*
	strcpy_sŠÖ”‚Íˆ—‚ÉŠÔ‚ª‚©‚©‚éB

*/
namespace Core
{
	String::String()
	{
		m_size = 0;
		m_capacity = 1;
		m_data = new char[m_capacity] {'\0'};
	}

	String::String(const size_t n, const char c)
	{
		m_size = n;
		m_capacity = m_size + 1;
		m_data = new char[m_capacity] {'\0'};
		for (size_t i = 0; i < m_size; i++)
			m_data[i] = c;
	}

	String::String(const char * c)
	{
		m_size = strlen(c);
		m_capacity = m_size + 1;
		m_data = new char[m_capacity];
		strcpy_s(m_data, m_capacity, c);
	}

	String::String(const char * front, const char * length)
	{
		m_size = reinterpret_cast<size_t>(length) - reinterpret_cast<size_t>(front);
		m_capacity = m_size + 1;
		m_data = new char[m_capacity];
		memcpy_s(this->m_data,this->m_capacity,front,this->m_size);
		m_data[this->m_size] = '\0';
	}

	String::String(const String & s)
	{
		m_capacity = s.m_capacity;
		m_size = s.m_size;
		m_data = new char[m_capacity];
		strcpy_s(m_data,m_capacity,s.m_data);
	}


	String::~String()
	{
		delete[] m_data;
	}

	const char & String::operator[](const size_t n) const
	{
		return m_data[n];
	}

	char & String::operator[](const size_t n)
	{
		return m_data[n];
	}

	String String::operator+(const char * c)
	{
		String result(*this);
		result += c;
		return result;
	}

	String String::operator+(const String & str)
	{
		String result(*this);
		result += str.m_data;
		return result;
	}

	String& String::operator+=(const char * c)
	{
		size_t size = this->m_size + strlen(c);
		if(this->m_capacity < size)
		{
			do
			{
				this->m_capacity *= 2;
			} while (this->m_capacity < size);
			
			char* data = new char[this->m_capacity];
			memcpy_s(data,this->m_capacity,this->m_data,this->m_size + 1);
			delete[] this->m_data;
			this->m_data = data;
		}

		strcat_s(this->m_data,this->m_capacity,c);
		this->m_size = size;
		return *this;
	}

	String & String::operator+=(const String & str)
	{
		size_t size = this->m_size + str.m_size;
		if(this->m_capacity < size)
		{
			do
			{
				this->m_capacity *= 2;
			} while (this->m_capacity < size);

			char* data = new char[this->m_capacity];
			memcpy_s(data,this->m_capacity,this->m_data,this->m_size + 1);
			delete[] this->m_data;
			this->m_data = data;
		}

		strcat_s(this->m_data,this->m_capacity,str.m_data);
		this->m_size = size;
		return *this;
	}

	bool String::operator == (const char *c) 
	{
		return m_size == strlen(c) && (memcmp(this->m_data, c, m_size) == 0);
	}

	bool String::empty() const
	{
		return this->m_size == 0;
	}

	size_t String::size() const
	{
		return this->m_size;
	}

	size_t String::length() const
	{
		return this->m_size;
	}

	size_t String::capacity() const
	{
		return this->m_capacity;
	}

	char & String::front() const
	{
		return this->m_data[0];
	}

	char & String::back() const
	{
		return this->m_data[this->m_size -1];
	}

	String String::substr(const size_t index, const size_t size) const
	{
		return String(this->m_data + index,this->m_data + index + size);
	}

	const char * String::c_str() const
	{
		return this->m_data;
	}

	const char * String::data() const
	{
		return this->m_data;
	}

	size_t String::find(const char * c, const size_t index) const
	{
		char* pos = strstr(this->m_data + index,c);
		return (pos == NULL) ? (std::string::npos) : (pos - this->m_data);
	}

}//namespace Core