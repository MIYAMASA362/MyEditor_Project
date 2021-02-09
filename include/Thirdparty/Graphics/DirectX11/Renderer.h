#pragma once
#ifndef THIRDPARTY_DIRECTX11_RENDERER_H
#define THIRDPARTY_DIRECTX11_RENDERER_H


namespace Platform
{
	namespace Graphics
	{
		/**
		* @class    class
		* @brief    Enum Description
		*/
		struct WindowSize
		{
			unsigned int width;
			unsigned int height;
		};

		/**
		* @class    DX11Renderer
		* @brief
		* 
		*	個別グラフィックス設定
		*	描画範囲の情報を持つ
		* 
		*/
		class ENGINE_API DX11Renderer : public ::Platform::Graphics::detail::IRenderer
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
			UINT m_ViewPortNum;

		public:
			DX11Renderer(HWND hWnd);
			virtual ~DX11Renderer();

			virtual void clear() override;
			virtual void begin() override;
			virtual void end() override;

		private:
			

		};//class DX11Renderer

	}// namespace ThirdParty::Platform::Graphics
}// namespace ThirdParty::Platform

#endif// ifndef THIRDPARTY_DIRECTX11_RENDERER_H