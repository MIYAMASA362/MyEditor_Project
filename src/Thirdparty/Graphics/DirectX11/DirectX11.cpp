// DirectX11.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include<io.h>

#include"Platform/Base/IRenderer.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"

using namespace DirectX;

DX11DeviceContext* g_pInstance = nullptr;

// DLL 処理
//namespace detail
//{
//	EXTERN_C ENGINE_API IGraphics* base_GetGraphics()
//	{
//		g_Instance = new DX11DeviceContext();
//		return g_Instance;
//	}
//
//	EXTERN_C ENGINE_API void base_ReleaseGraphics(IGraphics** instance)
//	{
//		delete dynamic_cast<DX11DeviceContext*>(*instance);
//		instance = nullptr;
//	}
//
//}// namesapce Platform::Graphics::detail

namespace Platform
{
	namespace detail
	{
		EXTERN_C ENGINE_API IRenderer* getIRenderer(RENDERER_DESC* pDesc)
		{
			return new DX11Renderer(pDesc->hWnd);
		}
	}
}


/*
*	DX11DeviceContext
*
*/
DX11DeviceContext::DX11DeviceContext()
	:
	m_FeatureLevel(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1),
	m_RendererCount(0)
{
	HRESULT hr = E_FAIL;

	UINT createDeviceFlags = 0;
#ifdef ENGINE_DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


	D3D_DRIVER_TYPE driveTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driveTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		D3D_DRIVER_TYPE type = driveTypes[driverTypeIndex];

		//Create a Device that represents the display adapter
		hr = D3D11CreateDevice(
			NULL,
			type,
			NULL,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&m_pD3DDevice,
			&m_FeatureLevel,
			&m_pImmediateContext
		);

		if (SUCCEEDED(hr)) break;
	}
	ASSERT(SUCCEEDED(hr), "DirectX11 D3DDeviceの作成に失敗しました。");

	//QuearyInterface
	//	IDXGIDevice1 のIntarfaceを取得
	//	D3D11Device は IUnkownクラスを継承している
	//	ref : https://docs.microsoft.com/ja-jp/cpp/atl/introduction-to-com?view=vs-2019
	//
	//	COMについて
	//	ref : http://chokuto.ifdef.jp/urawaza/com/com.html	
	//
	m_pD3DDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&m_pDXGI);

	//GetAdapter
	//	DeviceのApapter取得
	//	ref : https://docs.microsoft.com/ja-jp/windows/win32/api/dxgi/nn-dxgi-idxgidevice
	//
	m_pDXGI->GetAdapter(&m_pAdapter);

	//GetParent
	//	DXGIAdapterの親 IDXGIFactoryを取得
	//
	//	DXGIObject
	//	ref : https://docs.microsoft.com/ja-jp/windows/win32/api/dxgi/nn-dxgi-idxgiobject
	//
	m_pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pFactory);

	////ラスタライザステート設定
	{
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_BACK;
		rd.DepthClipEnable = TRUE;
		rd.MultisampleEnable = FALSE;

		ID3D11RasterizerState* rs;
		hr = m_pD3DDevice->CreateRasterizerState(&rd, &rs);
		ASSERT(SUCCEEDED(hr), "DirectX11 ラスタライザステートの作成に失敗しました。");

		m_pImmediateContext->RSSetState(rs);

		rs->Release();
	}

	//ブレンドステート設定
	{
		D3D11_RENDER_TARGET_BLEND_DESC rt;
		ZeroMemory(&rt, sizeof(rt));
		rt.BlendEnable = TRUE;
		rt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rt.BlendOp = D3D11_BLEND_OP_ADD;
		rt.SrcBlendAlpha = D3D11_BLEND_ONE;
		rt.DestBlendAlpha = D3D11_BLEND_ZERO;
		rt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = FALSE;
		bd.RenderTarget[0] = rt;

		float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
		ID3D11BlendState* blendState = NULL;
		hr = m_pD3DDevice->CreateBlendState(&bd, &blendState);
		ASSERT(SUCCEEDED(hr), "DirectX11 ブレンドステートの作成に失敗しました。");

		m_pImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);

		blendState->Release();
	}

	//サンプラーステート設定
	{
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.MipLODBias = 0;
		sd.MaxAnisotropy = 16;
		sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sd.MinLOD = 0;
		sd.MaxLOD = D3D11_FLOAT32_MAX;

		ID3D11SamplerState* ss = NULL;
		hr = m_pD3DDevice->CreateSamplerState(&sd, &ss);
		ASSERT(SUCCEEDED(hr), "DirectX サンプラーステートの作成に失敗しました。");

		m_pImmediateContext->PSSetSamplers(0, 1, &ss);

		ss->Release();
	}
}

DX11DeviceContext::~DX11DeviceContext()
{
	if (m_pImmediateContext) m_pImmediateContext->ClearState();

	if (m_pImmediateContext) m_pImmediateContext->Release();
	if (m_pFactory) m_pFactory->Release();
	if (m_pAdapter) m_pAdapter->Release();
	if (m_pDXGI) m_pDXGI->Release();
	if (m_pD3DDevice) m_pD3DDevice->Release();
}

DX11DeviceContext* DX11DeviceContext::GetInstance()
{
	if(g_pInstance == nullptr)
	{
		g_pInstance = new DX11DeviceContext();
	}

	return g_pInstance;
}

ID3D11Device* DX11DeviceContext::GetDevice()
{
	return m_pD3DDevice;
}

ID3D11DeviceContext* DX11DeviceContext::GetImmediateContext()
{
	return m_pImmediateContext;
}

HRESULT DX11DeviceContext::CreateSwapChain(OUT DXGI_SWAP_CHAIN_DESC* pDesc, OUT IDXGISwapChain** pSwapChain)
{
	return m_pFactory->CreateSwapChain(m_pD3DDevice, pDesc, pSwapChain);
}

HRESULT DX11DeviceContext::CreateRenderTargetView(IN ID3D11Resource* pResource, IN D3D11_RENDER_TARGET_VIEW_DESC* pDesc, OUT ID3D11RenderTargetView** ppRTView)
{
	return m_pD3DDevice->CreateRenderTargetView(pResource, pDesc, ppRTView);
}


/*
*	DX11Renderer
*
*/
DX11Renderer::DX11Renderer(HWND hWnd)
	:
	m_hWnd(hWnd)
{
	HRESULT hr = E_FAIL;

	// 画面サイズ取得
	RECT rect;
	GetClientRect(hWnd, &rect);
	LONG width = rect.right - rect.left;
	LONG height = rect.bottom - rect.top;

	// 
	DXGI_SAMPLE_DESC SampleDesc;
	SampleDesc.Count = 1;
	SampleDesc.Quality = 0;

	// 画面サイズ設定
	{
		this->m_width = width;
		this->m_height = height;
	}

	//スワップチェーン設定
	{
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc = SampleDesc;
		sd.Windowed = TRUE;

		hr = DX11DeviceContext::GetInstance()->CreateSwapChain(&sd,&m_pSwapChain);
		ASSERT(SUCCEEDED(hr), "DirectX11 SwapChainの生成に失敗しました。");
	}

	// レンダーターゲットビュー設定
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		this->m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		hr = DX11DeviceContext::GetInstance()->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
		pBackBuffer->Release();
		ASSERT(SUCCEEDED(hr), "Render Target Viewの生成に失敗しました。");
	}

	// ステンシル用テクスチャ設定
	{
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = width;
		td.Height = height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		td.SampleDesc = SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;

		// 深度テクスチャ
		ID3D11Texture2D* pDepthStencilTexture = NULL;
		hr = DX11DeviceContext::GetInstance()->GetDevice()->CreateTexture2D(&td, NULL, &pDepthStencilTexture);
		ASSERT(SUCCEEDED(hr), "DirectX11 DepthTextureの作成に失敗しました。");


		// 
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = td.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Flags = 0;

		// 
		hr = DX11DeviceContext::GetInstance()->GetDevice()->CreateDepthStencilView(pDepthStencilTexture, &dsvd, &m_pDepthStencilView);
		ASSERT(SUCCEEDED(hr), "DirectX11 StencilTextureの作成に失敗しました。");

		pDepthStencilTexture->Release();

		//コンテキストに設定
		DX11DeviceContext::GetInstance()->GetImmediateContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

		//深度ステンシルステート設定
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = FALSE;

		hr = DX11DeviceContext::GetInstance()->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateEnable);
		ASSERT(SUCCEEDED(hr), "DirectX11 深度ステンシル有効時ステートの作成に失敗しました。");

		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		hr = DX11DeviceContext::GetInstance()->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateDisable);
		ASSERT(SUCCEEDED(hr), "DirectX11 深度ステンシル無効時ステートの作成に失敗しました。");

		DX11DeviceContext::GetInstance()->GetImmediateContext()->OMSetDepthStencilState(m_pDepthStateEnable, NULL);
	}

	//ViewPort設定
	{
		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)height;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		m_ViewPortNum = 1;
		m_ViewPort = viewport;
		DX11DeviceContext::GetInstance()->GetImmediateContext()->RSSetViewports(m_ViewPortNum, &m_ViewPort);
	}

}

DX11Renderer::~DX11Renderer()
{
	if (m_pRenderTargetView) m_pRenderTargetView->Release();
	if (m_pDepthStencilView) m_pDepthStencilView->Release();

	if (m_pDepthStateEnable) m_pDepthStateEnable->Release();
	if (m_pDepthStateDisable) m_pDepthStateDisable->Release();

	if (m_pSwapChain) m_pSwapChain->Release();

}

void DX11Renderer::Clear()
{
	float color[4] = { 0.5f,0.5f,0.5f,1.0f };
	DX11DeviceContext::GetInstance()->GetImmediateContext()->RSSetViewports(m_ViewPortNum, &m_ViewPort);
	DX11DeviceContext::GetInstance()->GetImmediateContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	DX11DeviceContext::GetInstance()->GetImmediateContext()->ClearRenderTargetView(m_pRenderTargetView, color);
}

void DX11Renderer::Begin()
{
	DX11DeviceContext::GetInstance()->GetImmediateContext()->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11Renderer::End()
{
	m_pSwapChain->Present(0, 0);
}

void DX11Renderer::Release()
{
	delete this;
}