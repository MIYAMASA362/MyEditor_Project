#pragma once
#ifndef CORE_PATH_H
#define CORE_PATH_H

namespace Core
{
	/**
	* @class    Path
	* @brief    
	*/
	class Path final
	{
	private:
		std::string m_path;

	public:
		Path();
		Path(const char* path);
		Path(const std::string& path);
		~Path();

	public:
		bool isEnmpty() const;
		int lenght() const;
		const char* c_str() const;
		const std::string& str() const;

		/*
			return fileName that cutted extension and directory path in m_path;

			ex > Desktop/hogefile.txt => hogefile
		*/
		std::string getFileName() const;

		/*
			return file that cutted directory path in m_path;
		*/
		std::string getFile() const;
		
		/*
			return file that file extension
		*/
		std::string getExtension() const;



	};//class Path


}//namespace Core

#endif //ifndef CORE_PATH_H