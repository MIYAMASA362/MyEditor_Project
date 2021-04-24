#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Thirdparty/Graphics/DirectX11/DeviceContext.h"
#include"Thirdparty/Graphics/DirectX11/Renderer.h"

namespace Platform
{
	namespace detail
	{
		EXTERN_C ENGINE_API IRendererDevice* getIRendererDevice()
		{
			return new ThirdParty::DX11DeviceContext();
		}
	}
}


namespace ThirdParty
{
	/*
	*	DX11DeviceContext
	*
	*/
	DX11DeviceContext::DX11DeviceContext()
		:
		m_FeatureLevel(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1)
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

	Result DX11DeviceContext::CreateRenderer(IN HWND hWnd, OUT::Platform::IRenderer** pOutput)
	{
		DX11Renderer* result = new DX11Renderer(hWnd,this);

		(*pOutput) = result;

		return Result(true);
	}

	void DX11DeviceContext::Release()
	{
		delete this;
	}

}// namespace ThirdParty