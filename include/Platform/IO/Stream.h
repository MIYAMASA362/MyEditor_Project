#pragma once
#ifndef PLATFORM_STREAM_H
#define PLATFORM_STREAM_H

namespace Platform
{
	namespace IO
	{
		/*
		* @brief	StreamSeek
		*
		*/
		enum class StreamSeek
		{
			Begin,
			Current,
			End,
		};

		namespace detail
		{
			/**
			* @class    IStream
			* @brief    Stream interface
			*/
			class IStream
			{
			private:

			protected:
				IStream() = default;
				virtual ~IStream() = default;

			public:
				virtual bool isRead() const = 0;
				virtual bool isWrite() const = 0;

				virtual bool read(void* buffer, size_t size) = 0;
				virtual bool write(const void* buffer, size_t size) = 0;
				virtual void seek(int offset, StreamSeek seek) = 0;

			};//class Stream

		}//namespace detail
	}// namespace Platform::IO
}//namespace Platform

#endif //ifndef PLATFORM_STREAM_H