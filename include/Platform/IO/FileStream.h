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
			None = 0,				//設定なし
			Read = 1 << 0,			//読み込み
			Write = 1 << 1,			//書き込み
			ReadWrite = Read | Write,		//読み書き
		};

		constexpr FileMode operator&(FileMode a, FileMode b)
		{
			return static_cast<FileMode>(static_cast<u8>(a) & static_cast<u8>(b));
		};

		/**
		* @class    FileStream
		* @brief    ファイルの読み書き
		*/
		class FileStream : public detail::IStream
		{
		protected:
			std::string m_filePath;
			FileMode m_mode;
			FILE* m_stream = nullptr;

		public:
			/**
			*	@brief	ファイル生成
			*
			*	@in[string]	  :	ファイルパス
			*	@in[FileMode] : ファイルモード
			*
			*	@return[bool] : オープン・生成に成功/失敗(ファイル無し)
			*/
			static bool create(std::string filePath, FileMode mode, FileStream** output);

		protected:
			void open(const char* const fmode);

		public:
			FileStream(std::string filePath, FileMode mode);
			virtual ~FileStream();

			const std::string& getFilePath() const { return m_filePath; };

			/**
			*	@brief	ファイル開く
			*
			*	@return[bool] : オープンに成功/失敗(ファイル無し)
			*/
			bool open();
			void close();

			/* 読み込み可能か */
			virtual bool isRead() const override;

			/* 書き込み可能か */
			virtual bool isWrite() const override;


			/* 文字列読み込み */
			bool read(std::string& str);

			/* 文字列読み込み */
			virtual bool read(void* buffer, size_t size) override;

			/* フォーマット読み込み */
			template<typename... Args>
			bool readFormat(const char* format, Args... args)
			{
				return fscanf_s(m_stream, format, std::forward<Args>(args)...) != EOF;
			}

			/* 行を読み込みます */
			bool readline(void* offset, int size = 256);


			/* 文字列書き込み */
			bool write(std::string& str);

			/* 文字列書き込み */
			virtual bool write(const void* buffer, size_t size) override;

			/* フォーマット書き込み */
			template<typename... Args>
			int writeFormat(const char* format, Args... args)
			{
				return fprintf_s(m_stream, format, std::forward<Args>(args)...);
			}


			/* 文字列の検索
			*	@in[const char*] search : 検索する文字列
			*	@return[int] : strから見つけた相対位置[n] / 見つからない[-1]
			*/
			int find(const char* str, const char* search);

			/* 文字列の検索
			*	@in[const char*] search :検索する文字列
			*	@in[const char*] endstr	:検索終了する文字列
			*	@return[int] : strから見つけた相対位置[n] / 見つからない[-1]
			*/
			int find(const char* str, const char* search, const char* endstr);


			/**	検索文字列を探査し、検索文字列を含めた位置まで移動
			*	@in[const char* str] : 検索文字列
			*	@return[bool]	: 検索結果 見つかった[true] / 見つからない[false]
			*/
			bool seekFind(const char* str);

			/* 移動 */
			virtual void seek(int offset, StreamSeek seek) override;

			/* 次の行に移動します */
			void seekline(int offset);


			/* 現在位置 */
			long getPos() const;

			/* ファイルの全行数 */
			unsigned int lineNum() const;


		};// class FileStream
	}// namespace Platform::IO
}// namespace Platform

#endif // ifndef PLATFORM_FILESTREAM_H