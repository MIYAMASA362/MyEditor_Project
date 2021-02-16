#pragma once

#ifndef THIRDPARTY_DIRECTX11_SHADER_H
#define THIRDPARTY_DIRECTX11_SHADER_H

namespace Platform
{
	namespace Graphics
	{
		/**
		* @class    VertexShader
		* @brief    頂点シェーダ
		* 
		*/
		class ENGINE_API VertexShader : public detail::IVertexShader
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

			virtual void CreateShader(const void* buffer, const unsigned long size, VERTEX_INPUT_LAYOUT* inputLayout, unsigned int layoutSize);
			virtual void SetShader() override;
			virtual void SetInputLayout();


		};// class VertexShader



		/**
		* @class    PixelShader
		* @brief    ピクセルシェーダ
		* 
		*/
		class ENGINE_API PixelShader : public detail::IPixelShader
		{
		protected:
			ID3D11PixelShader* m_Source;

		public:
			PixelShader();
			virtual ~PixelShader();

			virtual void CreateShader(const void* buffer, const unsigned long size);
			virtual void SetShader() override;


		};// class PixelShader
		
		
		
	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_SHADER_H