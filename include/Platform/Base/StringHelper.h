#pragma once
#ifndef PLATFORM_STRINGHELPER_H
#define PLATFORM_STRINGHELPER_H

#include<string>

#define NOT_FIND (-1)

namespace Platform
{

	class StringHelper final
	{
	private:

		StringHelper() = default;
		~StringHelper() = default;
	public:

		/* •¶š—ñ‚ÌŒŸõ
		*	@in[const char*] search : ŒŸõ‚·‚é•¶š—ñ
		*	@return[int] : str‚©‚çŒ©‚Â‚¯‚½‘Š‘ÎˆÊ’u[n] / Œ©‚Â‚©‚ç‚È‚¢[-1]
		*/
		template<typename TChar>
		static int find(const TChar* str, const TChar* search);

		/* •¶š—ñ‚ÌŒŸõ
		*	@in[const char*] search :ŒŸõ‚·‚é•¶š—ñ
		*	@in[const char*] endstr	:ŒŸõI—¹‚·‚é•¶š—ñ
		*	@return[int] : str‚©‚çŒ©‚Â‚¯‚½‘Š‘ÎˆÊ’u[n] / Œ©‚Â‚©‚ç‚È‚¢[-1]
		*/
		template<typename TChar>
		static int find(const TChar* str, const TChar* search, const TChar* endstr);


		template<typename ...Args>
		static void format(char* buffer,const char* format,Args ...args);

		template<typename ...Args>
		static void format(wchar_t* buffer,const char* format,Args ...args);


	};//class StringHelper

	template<>
	inline int StringHelper::find<char>(const char * str, const char * search)
	{
		size_t str_len = strlen(str);
		size_t search_len = strlen(search);
		for(int i = 0; i < str_len; ++i,++str,--str_len)
		{
			if (str_len < search_len) break;
			if (strncmp(str, search, search_len) == 0) return i;
		}
		return NOT_FIND;
	}

	template<>
	inline int StringHelper::find<wchar_t>(const wchar_t * str, const wchar_t * search)
	{
		size_t str_len = wcslen(str);
		size_t search_len = wcslen(search);
		for(int i = 0; i < str_len; ++i,++str,--str_len)
		{
			if (wcsncmp(str, search, search_len) == 0) return i;
			if (str_len < search_len) break;
		}
		return NOT_FIND;
	}

	template<typename TChar>
	inline int StringHelper::find(const TChar * str, const TChar * search)
	{
		return NOT_FIND;
	}


	template<>
	inline int StringHelper::find<char>(const char * str, const char * search, const char * endstr)
	{
		size_t str_len = strlen(str);
		size_t search_len = strlen(search);
		size_t endstr_len = strlen(endstr);
		for(int i = 0; i < str_len; ++i,++str,--str_len)
		{
			if (str_len < search_len || str_len < endstr_len) break;
			if (strncmp(str, search, search_len) == 0) return i;
			if (strncmp(str, endstr, endstr_len) == 0) break;
		}
		return NOT_FIND;
	}

	template<>
	inline int StringHelper::find<wchar_t>(const wchar_t * str, const wchar_t * search, const wchar_t * endstr)
	{
		size_t str_len = wcslen(str);
		size_t search_len = wcslen(search);
		size_t endstr_len = wcslen(endstr);
		for (int i = 0; i < str_len; ++i, ++str, --str_len)
		{
			if (str_len < search_len || str_len < endstr_len) break;
			if (wcsncmp(str, search, search_len) == 0) return i;
			if (wcsncmp(str, endstr, endstr_len) == 0) break;
		}
		return NOT_FIND;
	}

	template<typename TChar>
	inline int StringHelper::find(const TChar * str, const TChar * search, const TChar * endstr)
	{
		return NOT_FIND;
	}

	template<typename ...Args>
	inline void StringHelper::format(char * buffer, const char * format, Args ...args)
	{
		sprintf(buffer, format, std::forward<Args>(args)...);
	}

	template<typename ...Args>
	inline void StringHelper::format(wchar_t * buffer, const char * format, Args ...args)
	{
		wsprintf(buffer,format,std::forward<Args>(args)...);
	}

}//namespace Platform

#endif //ifndef PLATFORM_STRINGHELPER_H