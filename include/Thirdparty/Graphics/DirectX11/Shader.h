#pragma once

#ifndef THIRDPARTY_DIRECTX11_SHADER_H
#define THIRDPARTY_DIRECTX11_SHADER_H

namespace Platform
{
	namespace Graphics
	{
		namespace Shaders
		{
			/**
			* @class    ConstantBuffer
			* @brief    定数バッファ
			*/
			class ConstantBuffer final
			{
			public:
				enum BUFFER_LAYOUT
				{
					BUFFER_WORLD = 0,
					BUFFER_VIEW,
					BUFFER_PROJECTION,
					BUFFER_NUM	// Size marker
				};

				ID3D11Buffer* m_Buffer[BUFFER_LAYOUT::BUFFER_NUM];

			public:
				ConstantBuffer();
				~ConstantBuffer();

				void CreateBuffer();

			};// class ConstantBuffer

			class Shader
			{
			protected:
				Shader() = default;
				void LoadShaderFile(const char* fileName,unsigned char** buffer,long int* fsize);

			public:
				virtual ~Shader() = default;

			};// class Shader

			class VertexShader : public Shader
			{
			public:
				enum class VERTEX_INPUT_LAYOUT
				{
					VSIL_POSITION,
					VSIL_NORMAL,
					VSIL_COLOR,
					VSIL_TEXCOORD
				};

			protected:
				ID3D11VertexShader* m_Source;
				ID3D11InputLayout* m_Layout;


			public:
				VertexShader();
				virtual ~VertexShader();

				virtual void CreateShader(const char* fileName, VERTEX_INPUT_LAYOUT* inputLayout, unsigned int layoutSize);

			};// class VertexShader

			class PixelShader : public Shader
			{
			protected:
				ID3D11PixelShader* m_Source;

			public:
				PixelShader();
				virtual ~PixelShader();

				virtual void CreateShader(const char* fileName);

			};// class PixelShader

		}// namespace Platform::Graphics::Shaders
	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_SHADER_H