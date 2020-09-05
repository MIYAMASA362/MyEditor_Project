#pragma once
#ifndef CORE_FILESTREAM_H
#define CORE_FILESTREAM_H

#include<fstream>

#include"Stream.h"

namespace Core
{
	/**
	*	@brief	FileMode
	*
	*/
	enum class FileMode : u8
	{
		None		= 0,				//設定なし
		Read		= 1 << 0,			//読み込み
		Write		= 1 << 1,			//書き込み
		ReadWrite	= Read | Write,		//読み書き
	};

	constexpr FileMode operator&(FileMode a,FileMode b)
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
		static bool create(std::string filePath,FileMode mode,FileStream** output);

	protected:
		void open(const char* const fmode);

	public:
		FileStream(std::string filePath,FileMode mode);
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
		
		/* フォーマット書き込み */
		template<typename... Args>
		int writeFormat(const char* format, Args... args)
		{
			return fprintf_s(m_stream, format, std::forward<Args>(args)...);
		}

		/* 行を読み込みます */
		bool readline(void* offset, int size = 256);


		/* 文字列書き込み */
		bool write(std::string& str);

		/* 文字列書き込み */
		virtual bool write(const void* buffer, size_t size) override;

		/* フォーマット読み込み */
		template<typename... Args>
		bool readFormat(const char* format, Args... args)
		{
			return fscanf_s(m_stream, format, std::forward<Args>(args)...) != EOF;
		}


		/* 移動 */
		virtual void seek(int offset,StreamSeek seek) override;
		
		/* 次の行に移動します */
		void seekline(int offset);

		/* 現在位置 */
		long getPos() const;

		/* ファイルの全行数 */
		unsigned int lineNum() const;


	};// class FileStream

}// namespace Core

#endif // ifndef FILESTREAM_H