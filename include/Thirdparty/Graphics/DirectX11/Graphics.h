#pragma once

#ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H
#define THIRDPARTY_DIRECTX11_GRAPHICS_H

/*
*	DirectX 11.h is a third party DirectX 11 wrapped header
*
*	class
*		�EDX11Graphics	DirecrX11 ���ʃO���t�B�b�N�X�ݒ�
*		�EDX11Renderer	DirectX11 �ʃO���t�B�b�N�X�ݒ�
*/

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{
			enum CONSTANT_BUFFER_ELEMENT
			{
				CONSTANT_BUFFER_WORLD = 0,
				CONSTANT_BUFFER_VIEW,
				CONSTANT_BUFFER_PROJECTION,
				CONSTANT_BUFFER_NUM
			};

			enum VERTEX_INPUT_LAYOUT
			{
				VSIL_POSITION,
				VSIL_NORMAL,
				VSIL_COLOR,
				VSIL_TEXCOORD
			};

		}

		/**
		* @class    DX11Graphics
		* @brief	DirectX11 ���ʃO���t�B�b�N�X�ݒ�
		*/
		class ENGINE_API DX11Graphics final : public ::Platform::Graphics::detail::IGraphics
		{
		private:
			IDXGIDevice1* m_pDXGI;
			IDXGIAdapter* m_pAdapter;
			IDXGIFactory* m_pFactory;

			ID3D11Device* m_pD3DDevice;
			ID3D11DeviceContext* m_pImmediateContext;

			D3D_FEATURE_LEVEL m_FeatureLevel;
			
		public:
			DX11Graphics();
			virtual ~DX11Graphics();

			static ID3D11Device* GetDevice();
			static ID3D11DeviceContext* GetImmediateContext();

			static HRESULT CreateSwapChain(DXGI_SWAP_CHAIN_DESC* pDesc,IDXGISwapChain** pSwapChain);
			static HRESULT CreateRenderTargetView(ID3D11Resource* pResource,D3D11_RENDER_TARGET_VIEW_DESC* pDesc,ID3D11RenderTargetView** ppRTView);

		public:
			virtual void CreateRenderer(HWND hWnd, Value_Type** output) override;
			virtual void ReleaseRenderer(Value_Type** instance) override;

		private:
			ID3D11Buffer* m_ConstantBuffer[detail::CONSTANT_BUFFER_ELEMENT::CONSTANT_BUFFER_NUM];

		public:
			void CreateConstantBuffer();

			void CreateVertexShader(const char* fileName,detail::VERTEX_INPUT_LAYOUT* inputLayout,unsigned int layoutSize);
			void CreatePiexelShader(const char* fileName);



		};//class DX11Graphics

	}//namespace Platform::Graphics
}//namespace Platform

#endif //ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H