#pragma once
#ifndef PLATFORM_FILESTREAM_H
#define PLATFORM_FILESTREAM_H

#include<fstream>

#include"Stream.h"

namespace Platform
{
	namespace IO
	{
		/**
		*	@brief	FileMode
		*
		*/
		enum class FileMode : u8
		{
			None = 0,				//�ݒ�Ȃ�
			Read = 1 << 0,			//�ǂݍ���
			Write = 1 << 1,			//��������
			ReadWrite = Read | Write,		//�ǂݏ���
		};

		constexpr FileMode operator&(FileMode a, FileMode b)
		{
			return static_cast<FileMode>(static_cast<u8>(a) & static_cast<u8>(b));
		};

		/**
		* @class    FileStream
		* @brief    �t�@�C���̓ǂݏ���
		*/
		class FileStream : public detail::IStream
		{
		protected:
			std::string m_filePath;
			FileMode m_mode;
			FILE* m_stream = nullptr;

		public:
			/**
			*	@brief	�t�@�C������
			*
			*	@in[string]	  :	�t�@�C���p�X
			*	@in[FileMode] : �t�@�C�����[�h
			*
			*	@return[bool] : �I�[�v���E�����ɐ���/���s(�t�@�C������)
			*/
			static bool create(std::string filePath, FileMode mode, FileStream** output);

		protected:
			void open(const char* const fmode);

		public:
			FileStream(std::string filePath, FileMode mode);
			virtual ~FileStream();

			const std::string& getFilePath() const { return m_filePath; };

			/**
			*	@brief	�t�@�C���J��
			*
			*	@return[bool] : �I�[�v���ɐ���/���s(�t�@�C������)
			*/
			bool open();
			void close();

			/* �ǂݍ��݉\�� */
			virtual bool isRead() const override;

			/* �������݉\�� */
			virtual bool isWrite() const override;


			/* ������ǂݍ��� */
			bool read(std::string& str);

			/* ������ǂݍ��� */
			virtual bool read(void* buffer, size_t size) override;

			/* �t�H�[�}�b�g�ǂݍ��� */
			template<typename... Args>
			bool readFormat(const char* format, Args... args)
			{
				return fscanf_s(m_stream, format, std::forward<Args>(args)...) != EOF;
			}

			/* �s��ǂݍ��݂܂� */
			bool readline(void* offset, int size = 256);


			/* �����񏑂����� */
			bool write(std::string& str);

			/* �����񏑂����� */
			virtual bool write(const void* buffer, size_t size) override;

			/* �t�H�[�}�b�g�������� */
			template<typename... Args>
			int writeFormat(const char* format, Args... args)
			{
				return fprintf_s(m_stream, format, std::forward<Args>(args)...);
			}


			/* ������̌���
			*	@in[const char*] search : �������镶����
			*	@return[int] : str���猩�������Έʒu[n] / ������Ȃ�[-1]
			*/
			int find(const char* str, const char* search);

			/* ������̌���
			*	@in[const char*] search :�������镶����
			*	@in[const char*] endstr	:�����I�����镶����
			*	@return[int] : str���猩�������Έʒu[n] / ������Ȃ�[-1]
			*/
			int find(const char* str, const char* search, const char* endstr);


			/**	�����������T�����A������������܂߂��ʒu�܂ňړ�
			*	@in[const char* str] : ����������
			*	@return[bool]	: �������� ��������[true] / ������Ȃ�[false]
			*/
			bool seekFind(const char* str);

			/* �ړ� */
			virtual void seek(int offset, StreamSeek seek) override;

			/* ���̍s�Ɉړ����܂� */
			void seekline(int offset);


			/* ���݈ʒu */
			long getPos() const;

			/* �t�@�C���̑S�s�� */
			unsigned int lineNum() const;


		};// class FileStream
	}// namespace Platform::IO
}// namespace Platform

#endif // ifndef PLATFORM_FILESTREAM_H