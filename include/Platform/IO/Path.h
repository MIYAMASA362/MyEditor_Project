#pragma once
#ifndef PLATFORM_PATH_H
#define PLATFORM_PATH_H

namespace Platform
{
	namespace IO
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
			size_t lenght() const;
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



		};// class Path
	}// namespace Platform::IO
}//namespace Platform

#endif //ifndef PLATFORM_PATH_H