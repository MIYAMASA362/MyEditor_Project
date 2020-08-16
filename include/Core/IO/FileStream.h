#pragma once
#ifndef FILESTREAM_H
#define FILESTREAM_H

namespace Core
{
	/**
	*	@brief	FileMode
	*
	*/
	enum class FileMode
	{
		None = 0x00,				//�ݒ�Ȃ�
		Read = 0x01,				//�ǂݍ���
		Write = 0x02,				//��������
		ReadWrite = Read | Write,	//�ǂݏ���
		Create = 0x04,
	};

	static FileMode operator|(FileMode a, FileMode b)
	{
		return static_cast<FileMode>(static_cast<u64>(a) | static_cast<u64>(b));
	}

	static FileMode operator&(FileMode a, FileMode b)
	{
		return static_cast<FileMode>(static_cast<u64>(a) & static_cast<u64>(b));
	}

	/**
	*	@brief FileSeek
	*
	*/
	enum class FileSeek
	{
		Begin,			//�擪
		Cursor,			//����
		End,			//����
	};

	namespace detail
	{
		/**
		* @class    FileStream Interface
		* @brief    �t�@�C���̓ǂݏ���
		*/
		class IFileStream
		{
		protected:
			char* m_fileName;
			FileMode m_fileMode;

		public:
			IFileStream() {};
			virtual ~IFileStream() {};

			virtual Result open(const char* fileName, FileMode fileMode) = 0;
			virtual Result close() = 0;

			virtual void write(void* textBuffer, size_t size) = 0;
			virtual void read(void* textBuffer, size_t size) = 0;

			virtual void seek(size_t offset,FileSeek seek) = 0;

			bool isWrite() { return (m_fileMode & FileMode::Write) == FileMode::Write; };
			bool isRead() { return (m_fileMode & FileMode::Read) == FileMode::Read; };

		};// class FileStream

	}// namespace Core::detail

	/**
	* @class    FileStream
	* @brief    Windows fstream�𗘗p�������o��
	*/
	class FileStream : public detail::IFileStream
	{
	private:
		std::fstream m_fstream;

	public:
		FileStream();
		virtual ~FileStream();

		virtual Result open(const char* fileName, FileMode fileMode) override;
		virtual Result close() override;

		virtual void seek(size_t offset,FileSeek seek) override;

		virtual void write(void* textBuffer, size_t size) override;
		void write(std::string text);

		virtual void read(void* textBuffer,size_t size) override;
		void read(std::string& text);

		void getline(std::string& text);

	};// class FileStream

}// namespace Core

#endif // ifndef FILESTREAM_H