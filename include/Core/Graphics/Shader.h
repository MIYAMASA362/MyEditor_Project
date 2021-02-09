#pragma once
#ifndef CORE_SHADER_H
#define CORE_SHADER_H

namespace Core
{
	namespace Graphics
	{
		/**
		* @class    PixelShader
		* @brief    Enum Description
		*/
		class PixelShader
		{
		private:

		public:
			PixelShader();
			virtual ~PixelShader();

		};// class PixelShader

		/**
		* @class    VertexShader
		* @brief    Enum Description
		*/
		class VertexShader
		{
		private:

		public:
			VertexShader();
			virtual ~VertexShader();

		};// class VertexShader

	}// namespace Core::Graphics
}// namespace Core

#endif // ifndef CORE_SHADER_H