#pragma once
#ifndef THIRDPARTY_DIRECTX11_H
#define THIRDPARTY_DIRECTX11_H

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")

using namespace DirectX;

/**
* @class    DX11DeviceContext
* @brief	DirectX11 共通グラフィックス設定
*/
class DX11DeviceContext final
{
public:
	static DX11DeviceContext* GetInstance();

	static void Create();
	static void Release();

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

	DX11DeviceContext();
	virtual ~DX11DeviceContext();

private:
	static DX11DeviceContext* g_pInstance;

	IDXGIDevice1* m_pDXGI;
	IDXGIAdapter* m_pAdapter;
	IDXGIFactory* m_pFactory;

	ID3D11Device* m_pD3DDevice;
	ID3D11DeviceContext* m_pImmediateContext;

	D3D_FEATURE_LEVEL m_FeatureLevel;

};//class DX11DeviceContext


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
	DX11Renderer(HWND hWnd);
	~DX11Renderer();

	virtual void Clear() override;
	virtual void Begin() override;
	virtual void End() override;

	virtual void Release() override;

private:
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

#endif //ifndef THIRDPARTY_DIRECTX11_H