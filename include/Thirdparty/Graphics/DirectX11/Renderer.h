#pragma once
#ifndef THIRDPARTY_RENDERER_H
#define THIRDPARTY_RENDERER_H

namespace ThirdParty
{
	/**
	* @class    DX11Renderer
	* @brief
	*
	*	個別グラフィックス設定
	*	描画範囲の情報を持つ
	*
	*/
	class DX11Renderer final : public Platform::IRenderer
	{
	public:
		DX11Renderer(HWND hWnd, DX11DeviceContext* device);
		~DX11Renderer();

		virtual void Clear() override;
		virtual void Begin() override;
		virtual void End() override;

		virtual void Release() override;

	private:
		DX11DeviceContext* m_pDeviceContext;

		HWND m_hWnd;
		unsigned int m_height;
		unsigned int m_width;

		IDXGISwapChain* m_pSwapChain;

		ID3D11RenderTargetView* m_pRenderTargetView;
		ID3D11DepthStencilView* m_pDepthStencilView;

		ID3D11DepthStencilState* m_pDepthStateEnable;
		ID3D11DepthStencilState* m_pDepthStateDisable;

		D3D11_VIEWPORT m_ViewPort;
		UINT m_ViewPortNum;

	};//class DX11Renderer

}// namespace ThirdParty

#endif // ifndef THIRDPARTY_RENDERER_H