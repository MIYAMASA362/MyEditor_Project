#pragma once
#ifndef PLATFORM_ISHADER_H
#define PLATFORM_ISHADER_H

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{
			/**
			* @class    Shader Interface
			* @brief    シェーダインターフェイス
			* 
			* 
			*/
			class ENGINE_API IShader
			{
			public:
				IShader() = default;
				virtual ~IShader() = default;

				// シェーダを適用させる
				virtual void SetShader() = 0;

			};// class IShader


			/**
			* @class    IVertexShader
			* @brief	頂点シェーダ
			* 
			* 
			*/
			class ENGINE_API IVertexShader : public IShader
			{
			public:
				IVertexShader() = default;
				virtual ~IVertexShader() = default;

				virtual void CreateShader(const void* buffer,const unsigned long size) = 0;

			};// class IVertexShader


			/**
			* @class    IPixelShader
			* @brief    ピクセルシェーダ
			* 
			* 
			*/
			class ENGINE_API IPixelShader : public IShader
			{
			public:
				IPixelShader() = default;
				virtual ~IPixelShader() = default;

				virtual void CreateShader(const void* buffer,const unsigned long size) = 0;

			};// class IPixelShader

		}// namespace Platform::Graphics::detail
	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef PLATFORM_ISHADER_H