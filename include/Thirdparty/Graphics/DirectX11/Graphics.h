#pragma once

#ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H
#define THIRDPARTY_DIRECTX11_GRAPHICS_H

/*
*	DirectX 11.h is a third party DirectX 11 wrapped header
*	
*	class 
*		・DX11Graphics	DirecrX11 共通グラフィックス設定
*		・DX11Renderer	DirectX11 個別グラフィックス設定
*/

namespace ThirdParty
{
	namespace Platform
	{
		namespace Graphics
		{
			struct WindowSize
			{
				unsigned int width;
				unsigned int height;
			};

			/**
			* @class    DX11Graphics
			* @brief	DirectX11 共通グラフィックス設定
			*/
			class ENGINE_API DX11Graphics final : public ::detail::Singleton<DX11Graphics>
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
				static HRESULT CreateRenderTargetView(ID3D11Resource* pResource,D3D11_RENDER_TARGET_VIEW_DESC* pDesc,ID3D11RenderTargetView ** ppRTView);

			};//class DX11Graphics

			/**
			* @class    DX11Renderer
			* @brief
			*/
			class ENGINE_API DX11Renderer : public ::Platform::detail::IRenderer
			{
			protected:
				HWND m_hWnd;
				WindowSize m_WindowSize;

				IDXGISwapChain* m_pSwapChain;

				ID3D11RenderTargetView* m_pRenderTargetView;
				ID3D11DepthStencilView* m_pDepthStencilView;

				ID3D11DepthStencilState* m_pDepthStateEnable;
				ID3D11DepthStencilState* m_pDepthStateDisable;

				D3D11_VIEWPORT m_ViewPort;
				unsigned int m_ViewPortNum;

			public:
				DX11Renderer(HWND hWnd);
				virtual ~DX11Renderer();

				virtual void clear() override;
				virtual void begin() override;
				virtual void end() override;

			};//class DX11Renderer

		}//namespace ThirdParty::Platform::Graphics
	}//namespace ThirdParty::Platform
}// namespace ThirdParty
#endif //ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H