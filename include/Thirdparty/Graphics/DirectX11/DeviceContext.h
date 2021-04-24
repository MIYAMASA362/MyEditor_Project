#pragma once
#ifndef THIRDPARTY_DEVICECONTEXT_H
#define THIRDPARTY_DEVICECONTEXT_H

namespace ThirdParty
{
	/**
	* @class    DX11DeviceContext
	* @brief	DirectX11 共通グラフィックス設定
	*/
	class DX11DeviceContext final : public Platform::IRendererDevice
	{
	public:
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetImmediateContext();

		HRESULT CreateSwapChain(
			OUT DXGI_SWAP_CHAIN_DESC* pDesc,
			OUT IDXGISwapChain** pSwapChain
		);

		HRESULT CreateRenderTargetView(
			IN ID3D11Resource* pResource,
			IN D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			OUT ID3D11RenderTargetView** ppRTView
		);

		virtual Result CreateRenderer(
			IN HWND hWnd,
			OUT Platform::IRenderer** pOutput
		) override;

		virtual void Release() override;

		DX11DeviceContext();
		virtual ~DX11DeviceContext();

	private:
		IDXGIDevice1* m_pDXGI;
		IDXGIAdapter* m_pAdapter;
		IDXGIFactory* m_pFactory;

		ID3D11Device* m_pD3DDevice;
		ID3D11DeviceContext* m_pImmediateContext;

		D3D_FEATURE_LEVEL m_FeatureLevel;

	};//class DX11DeviceContext

}// namespace ThirdParty

#endif // ifndef THIRDPARTY_DEVICECONTEXT_H