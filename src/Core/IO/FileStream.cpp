#include"Core/IO/Common.h"
#include"Core/IO/FileStream.h"

namespace Core
{
	FileStream::FileStream()
	{

	}

	FileStream::~FileStream()
	{
		m_fstream.close();
	}

	Result FileStream::open(const char * fileName, FileMode fileMode)
	{
		//�V�K�쐬
		if((fileMode & FileMode::Create) == FileMode::Create)
		{
			//�V�K�t�@�C���̍쐬(�����t�@�C���̓��e�j��)
			std::ofstream ofs(fileName,std::ios_base::out);
			if(!ofs)
			{
				LOG_FATAL("�t�@�C���̃I�[�v���Ɏ��s���܂����B(file : %s)",fileName);
				return Result(false);
			}
			LOG_DEBUG("�t�@�C�����쐬�A�܂��͓��e�̔j�������܂����B(file : %s)", fileName);
		}

		this->m_fileMode = fileMode;

		//�t�@�C���̃I�[�v�����[�h
		unsigned int mode = 0;
		if (isWrite()) mode |= std::ios_base::in;
		if (isRead()) mode |= std::ios_base::out;

		//�t�@�C���̃I�[�v��
		m_fstream.open(fileName,mode);
		if(!m_fstream)
		{
			LOG_FATAL("�t�@�C���̃I�[�v���Ɏ��s���܂����B(file : %s)",fileName);
			this->m_fileMode = FileMode::None;
			return Result(false);
		}

		return Result(true);
	}

	Result FileStream::close()
	{
		m_fstream.close();
		return Result(true);
	}

	void FileStream::seek(size_t offset, FileSeek fileSeek)
	{
		unsigned int seek = 0;
		if (fileSeek == FileSeek::Cursor)
			seek = std::ios_base::cur;
		else if (fileSeek == FileSeek::End)
			seek = std::ios_base::end;
		else
			seek = std::ios_base::beg;

		m_fstream.seekg(offset,seek);
	}

	void FileStream::write(void * textBuffer, size_t size)
	{
		if(isWrite()) m_fstream.write((char*)textBuffer,size);
	}

	void FileStream::write(std::string text)
	{
		if(isWrite())m_fstream << text;
	}

	void FileStream::read(void * textBuffer, size_t size)
	{
		if(isRead()) m_fstream.read((char*)textBuffer,size);
	}

	void FileStream::read(std::string& text)
	{
		if(isRead()) m_fstream >> text;
	}

	void FileStream::getline(std::string& text)
	{
		if (isRead()) std::getline(this->m_fstream,text);
	}

}// namespace Core