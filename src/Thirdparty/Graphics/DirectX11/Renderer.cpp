#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/Graphics.h"
#include"Thirdparty/Graphics/DirectX11/Renderer.h"


namespace Platform
{
	namespace Graphics
	{
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
				this->m_WindowSize.width = width;
				this->m_WindowSize.height = height;
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

				hr = DX11Graphics::CreateSwapChain(&sd, &this->m_pSwapChain);
				ASSERT(SUCCEEDED(hr), "DirectX11 SwapChainの生成に失敗しました。");
			}

			// レンダーターゲットビュー設定
			{
				ID3D11Texture2D* pBackBuffer = NULL;
				this->m_pSwapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				hr = DX11Graphics::CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
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
				hr = DX11Graphics::GetDevice()->CreateTexture2D(&td, NULL, &pDepthStencilTexture);
				ASSERT(SUCCEEDED(hr), "DirectX11 DepthTextureの作成に失敗しました。");


				// 
				D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
				ZeroMemory(&dsvd, sizeof(dsvd));
				dsvd.Format = td.Format;
				dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				dsvd.Flags = 0;

				// 
				hr = DX11Graphics::GetDevice()->CreateDepthStencilView(pDepthStencilTexture, &dsvd, &m_pDepthStencilView);
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
			}

			//ViewPort設定
			{
				CD3D11_VIEWPORT viewport;
				viewport.Width = (FLOAT)width;
				viewport.Height = (FLOAT)height;
				viewport.MinDepth = 0.0f;
				viewport.MaxDepth = 1.0f;
				viewport.TopLeftX = 0;
				viewport.TopLeftY = 0;

				m_ViewPortNum = 1;
				m_ViewPort = viewport;
				DX11Graphics::GetImmediateContext()->RSSetViewports(m_ViewPortNum, &m_ViewPort);
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

		//void DX11Renderer::setRasterizer(FILL_MODE fillmode, CULL_MODE cullmode)
		//{
		//	D3D11_RASTERIZER_DESC rd;
		//	ZeroMemory(&rd,sizeof(rd));
		//	rd.FillMode = (D3D11_FILL_MODE)fillmode;
		//	rd.CullMode = (D3D11_CULL_MODE)cullmode;
		//	rd.DepthClipEnable = TRUE;
		//	rd.MultisampleEnable = FALSE;

		//	ID3D11RasterizerState* rs;
		//	HRESULT hr = DX11Graphics::GetDevice()->CreateRasterizerState(&rd,&rs);
		//	ASSERT(SUCCEEDED(hr), "DirectX11 ラスタライザステートの作成に失敗しました。");

		//	DX11Graphics::GetImmediateContext()->RSSetState(rs);
		//}

		//void DX11Renderer::setBlenderState(UINT renderTargetNum, BOOL enable)
		//{
		//	if (enable == TRUE) renderTargetNum = 0;

		//	D3D11_RENDER_TARGET_BLEND_DESC rt;
		//	ZeroMemory(&rt,sizeof(rt));
		//	rt.BlendEnable = enable;
		//	rt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		//	rt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		//	rt.BlendOp = D3D11_BLEND_OP_ADD;
		//	rt.SrcBlendAlpha = D3D11_BLEND_ONE;
		//	rt.DestBlendAlpha = D3D11_BLEND_ZERO;
		//	rt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		//	rt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		//	D3D11_BLEND_DESC bd;
		//	ZeroMemory(&bd,sizeof(bd));
		//	/*
		//	*	AlphaToCoverageを行うかのフラグ
		//	*		TRUE : 有効化 / FALSE: 無効化
		//	*/
		//	bd.AlphaToCoverageEnable = FALSE;
		//	/*
		//	*	レンダーターゲット毎に異なるブレンディングを行うか決めるフラグ
		//	*		TRUE : 有効化
		//	*		FALSE: RenderTarget[0]の内容が全てのレンダーターゲットで使用される
		//	*/
		//	bd.IndependentBlendEnable = FALSE;
		//	bd.RenderTarget[renderTargetNum] = rt;

		//	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
		//	ID3D11BlendState* blendState = NULL;
		//	HRESULT hr = DX11Graphics::GetDevice()->CreateBlendState(&bd,&blendState);
		//	ASSERT(SUCCEEDED(hr), "DirectX11 ブレンドステートの作成に失敗しました。");

		//	DX11Graphics::GetImmediateContext()->OMSetBlendState(blendState,blendFactor, 0xFFFFFF);
		//}

	}// namespace ThirdParty::Platform::Graphics
}// namespace ThirdParty::Platform