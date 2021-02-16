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
			* @brief    �V�F�[�_�C���^�[�t�F�C�X
			* 
			* 
			*/
			class ENGINE_API IShader
			{
			public:
				IShader() = default;
				virtual ~IShader() = default;

				// �V�F�[�_��K�p������
				virtual void SetShader() = 0;

			};// class IShader


			/**
			* @class    IVertexShader
			* @brief	���_�V�F�[�_
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
			* @brief    �s�N�Z���V�F�[�_
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