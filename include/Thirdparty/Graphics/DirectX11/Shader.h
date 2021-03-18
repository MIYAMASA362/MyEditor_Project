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
		class VertexShader : public IVertexShader
		{
		protected:
			ID3D11VertexShader* m_Source;
			ID3D11InputLayout* m_Layout;

		public:
			VertexShader(
				ID3D11Device* pDevice,
				const void* buffer,
				const unsigned long size,
				VERTEX_INPUT_LAYOUT* inputLayout,
				unsigned int layoutSize
			);
			virtual ~VertexShader();

			virtual void SetShaderResource() override;
			virtual void SetInputLayout();

			virtual void Release() override;

		};// class VertexShader



		/**
		* @class    PixelShader
		* @brief    ピクセルシェーダ
		* 
		*/
		class PixelShader : public IPixelShader
		{
		protected:
			ID3D11PixelShader* m_Source;

		public:
			PixelShader(
				ID3D11Device* pDevice,
				const void* buffer,
				const unsigned long size
			);
			virtual ~PixelShader();

			virtual void SetShaderResource() override;

			virtual void Release() override;

		};// class PixelShader
		
		
		
	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_SHADER_H