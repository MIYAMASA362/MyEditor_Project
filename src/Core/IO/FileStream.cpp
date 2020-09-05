#include"stdafx.h"

#include<iostream>

#include"Core/Base/Logger.h"
#include"Core/Base/Result.h"

#include"Core/IO/FileStream.h"

#define FREAD_BUFFER_SIZE (256)

namespace Core
{
	FileStream::FileStream(std::string filePath, FileMode mode)
		:
		m_filePath(filePath),
		m_mode(mode)
	{

	}

	FileStream::~FileStream()
	{
		close();
	}

	bool FileStream::create(std::string filePath, FileMode mode,FileStream** output)
	{
		if (mode == FileMode::None) return false;

		FileStream* result = new FileStream(filePath, mode);

		//書き込み読み込み
		if((mode & FileMode::ReadWrite) == FileMode::ReadWrite)
		{
			result->open("w+");
		}
		//書き込み
		else if(result->isWrite())
		{
			result->open("w");
		}
		//読み込み
		else
		{
			result->open("w");
			result->close();
			result->open("r");
		}

		//ファイルオープン成功
		if(result->m_stream != nullptr)
		{
			(*output) = result;
			return true;
		}

		//ファイルオープン失敗
		delete result;
		return false;
	}

	void FileStream::open(const char* const fmode)
	{
		fopen_s(&m_stream, m_filePath.c_str(), fmode);
	}

	bool FileStream::open()
	{
		if (m_mode == FileMode::None) return false;

		if (isWrite() == true)
			this->open("r+");
		else
			this->open("r");

		return m_stream != nullptr;
	}

	void FileStream::close()
	{
		if (m_stream == nullptr) return;
		fclose(m_stream);
	}

	bool FileStream::isRead() const
	{
		return ((m_mode & FileMode::Read) == FileMode::Read);
	}

	bool FileStream::isWrite() const
	{
		return ((m_mode & FileMode::Write) == FileMode::Write);
	}

	bool FileStream::read(std::string & str)
	{
		this->read(&str[0], str.capacity());

		return true;
	}

	bool FileStream::read(void * buffer, size_t size)
	{
		if (!isRead()) return false;

		fread(buffer,sizeof(char),size,m_stream);

		return true;
	}

	bool FileStream::write(std::string & str)
	{
		return this->write(str.c_str(),str.size());
	}

	bool FileStream::write(const void * textBuffer, size_t size)
	{
		if (!isWrite()) return false;

		fwrite(textBuffer, sizeof(char), size, m_stream);

		return true;
	}

	void FileStream::seek(int offset, StreamSeek seek)
	{
		int origin = SEEK_CUR;
		if (seek == StreamSeek::Begin)
		{
			origin = SEEK_SET;
		}
		else if (seek == StreamSeek::End)
		{
			origin = SEEK_END;
		}

		fseek(m_stream, offset, origin);
	}

	void FileStream::seekline(int offset)
	{
		char buffer[256];
		this->readline(&buffer[0], 256);
		this->seek(offset,Core::StreamSeek::Current);
	}

	long FileStream::getPos() const
	{
		return ftell(m_stream);
	}

	unsigned int FileStream::lineNum() const
	{
		char buffer[FREAD_BUFFER_SIZE];
		unsigned int line = 0;
		size_t size;
		while((size = fread(buffer,1,FREAD_BUFFER_SIZE,m_stream)) > 0)
		{
			for (size_t i = 0; i < size; i++) {
				if (buffer[i] == '\n') line++;
			}
		}

		return line;
	}

	bool FileStream::readline(void * offset, int size)
	{
	 	return fgets((char*)offset,size,m_stream) != NULL;
	}


}// namespace Core