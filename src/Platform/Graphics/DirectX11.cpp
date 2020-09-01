#define ENGINE_DIRECTX11
#include"Platform/Common.h"
#include"Platform/Base/IRenderer.h"
#include"Platform/DesignPattern/Singleton.h"
#include"Platform/Graphics/DirectX11.h"

#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

namespace Platform
{
	namespace Graphics
	{
		/*
		*	DX11Graphics
		*
		*/

		DX11Graphics::DX11Graphics()
		{
			HRESULT hr = E_FAIL;
			D3D_FEATURE_LEVEL featureLevels[1] = { D3D_FEATURE_LEVEL_11_0 };

			//Create a Device that represents the display adapter
			hr = D3D11CreateDevice(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				0,
				featureLevels,
				1,
				D3D11_SDK_VERSION,
				&m_pD3DDevice,
				&m_FeatureLevel,
				&m_pImmediateContext
			);

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

			//ラスタライザステート設定
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


			//ブレンドステート設定
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

			//サンプラーステート設定
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
		}

		DX11Graphics::~DX11Graphics()
		{
			if (m_pImmediateContext) m_pImmediateContext->ClearState();

			if (m_pImmediateContext) m_pImmediateContext->Release();
			if (m_pFactory) m_pFactory->Release();
			if (m_pAdapter) m_pAdapter->Release();
			if (m_pDXGI) m_pDXGI->Release();
			if (m_pD3DDevice) m_pD3DDevice->Release();
		}

		ID3D11Device * DX11Graphics::GetDevice()
		{
			return GetInstance()->m_pD3DDevice;
		}

		ID3D11DeviceContext * DX11Graphics::GetImmediateContext()
		{
			return GetInstance()->m_pImmediateContext;
		}

		HRESULT DX11Graphics::CreateSwapChain(DXGI_SWAP_CHAIN_DESC * pDesc, IDXGISwapChain ** pSwapChain)
		{
			return GetInstance()->m_pFactory->CreateSwapChain(GetInstance()->m_pD3DDevice,pDesc,pSwapChain);
		}

		HRESULT DX11Graphics::CreateRenderTargetView(ID3D11Resource * pResource, D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView ** ppRTView)
		{
			return GetDevice()->CreateRenderTargetView(pResource,pDesc,ppRTView);
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

			//
			RECT rect;
			GetClientRect(hWnd, &rect);
			this->m_WindowSize.width = rect.right - rect.left;
			this->m_WindowSize.height = rect.bottom - rect.top;

			//
			DXGI_MODE_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			bufferDesc.Width = this->m_WindowSize.width;
			bufferDesc.Height = this->m_WindowSize.height;
			bufferDesc.RefreshRate.Numerator = 60;
			bufferDesc.RefreshRate.Denominator = 1;

			//
			DXGI_SAMPLE_DESC sampleDesc;
			ZeroMemory(&sampleDesc, sizeof(sampleDesc));
			sampleDesc.Count = 1;
			sampleDesc.Quality = 0;

			//スワップチェーン設定
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.OutputWindow = hWnd;
			sd.Windowed = TRUE;
			sd.BufferCount = 1;
			sd.BufferDesc = bufferDesc;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.SampleDesc = sampleDesc;

			hr = DX11Graphics::CreateSwapChain(&sd, &this->m_pSwapChain);
			ASSERT(SUCCEEDED(hr), "DirectX11 SwapChainの生成に失敗しました。");

			//レンダーターゲットビュー設定
			ID3D11Texture2D* pBackBuffer = NULL;
			this->m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			hr = DX11Graphics::CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
			pBackBuffer->Release();

			//ステンシル用テクスチャ設定
			ID3D11Texture2D* depthTexture = NULL;
			D3D11_TEXTURE2D_DESC td;
			ZeroMemory(&td, sizeof(td));
			td.Width = bufferDesc.Width;
			td.Height = bufferDesc.Height;
			td.MipLevels = 1;
			td.ArraySize = 1;
			td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			td.SampleDesc = sampleDesc;
			td.Usage = D3D11_USAGE_DEFAULT;
			td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			td.CPUAccessFlags = 0;
			td.MiscFlags = 0;

			hr = DX11Graphics::GetDevice()->CreateTexture2D(&td, NULL, &depthTexture);
			ASSERT(SUCCEEDED(hr), "DirectX11 DepthTextureの作成に失敗しました。");

			//
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
			ZeroMemory(&dsvd, sizeof(dsvd));
			dsvd.Format = td.Format;
			dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvd.Flags = 0;

			hr = DX11Graphics::GetDevice()->CreateDepthStencilView(depthTexture, &dsvd, &m_pDepthStencilView);
			ASSERT(SUCCEEDED(hr), "DirectX11 StencilTextureの作成に失敗しました。");

			//コンテキストに設定
			DX11Graphics::GetImmediateContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

			//深度ステンシルステート設定
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
			depthStencilDesc.DepthEnable = TRUE;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			depthStencilDesc.StencilEnable = FALSE;

			hr = DX11Graphics::GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateEnable);
			ASSERT(SUCCEEDED(hr), "DirectX11 深度ステンシル有効時ステートの作成に失敗しました。");

			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			hr = DX11Graphics::GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStateDisable);
			ASSERT(SUCCEEDED(hr), "DirectX11 深度ステンシル無効時ステートの作成に失敗しました。");

			DX11Graphics::GetImmediateContext()->OMSetDepthStencilState(m_pDepthStateEnable, NULL);

			//ViewPort設定
			CD3D11_VIEWPORT viewport;
			viewport.Width = (FLOAT)bufferDesc.Width;
			viewport.Height = (FLOAT)bufferDesc.Height;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;

			m_ViewPortNum = 1;
			m_ViewPort = viewport;
			DX11Graphics::GetImmediateContext()->RSSetViewports(m_ViewPortNum, &m_ViewPort);

		}

		DX11Renderer::~DX11Renderer()
		{
			if (m_pRenderTargetView) m_pRenderTargetView->Release();
			if (m_pDepthStencilView) m_pDepthStencilView->Release();

			if (m_pDepthStateEnable) m_pDepthStateEnable->Release();
			if (m_pDepthStateDisable) m_pDepthStateDisable->Release();

			if (m_pSwapChain) m_pSwapChain->Release();
		}

		void DX11Renderer::clear()
		{
			float color[4] = { 0.5f,0.5f,0.5f,1.0f };
			DX11Graphics::GetImmediateContext()->RSSetViewports(m_ViewPortNum, &m_ViewPort);
			DX11Graphics::GetImmediateContext()->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
			DX11Graphics::GetImmediateContext()->ClearRenderTargetView(m_pRenderTargetView, color);
		}

		void DX11Renderer::begin()
		{
			DX11Graphics::GetImmediateContext()->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		}

		void DX11Renderer::end()
		{
			m_pSwapChain->Present(0, 0);
		}

	}//namespace Platform::Graphics
}//namepsace Platform