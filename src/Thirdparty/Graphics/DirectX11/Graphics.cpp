// DirectX11.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"

#include<io.h>

#include"Thirdparty/Graphics/DirectX11/Graphics.h"
#include"Thirdparty/Graphics/DirectX11/Renderer.h"

using namespace DirectX;

namespace Platform
{
	namespace Graphics
	{
		static DX11Graphics* g_Instance = nullptr;

		namespace detail
		{
			EXTERN_C ENGINE_API IGraphics* base_GetGraphics()
			{
				g_Instance = new DX11Graphics();
				return g_Instance;
			}

			EXTERN_C ENGINE_API void base_ReleaseGraphics(IGraphics** instance)
			{
				delete g_Instance;
				g_Instance = nullptr;
			}

		}// namesapce Platform::Graphics::detail


		/*
		*	DX11Graphics
		*
		*/

		DX11Graphics::DX11Graphics()
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

			//ラスタライザステート設定
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
			}
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

		ID3D11Device* DX11Graphics::GetDevice()
		{
			return g_Instance->m_pD3DDevice;
		}

		ID3D11DeviceContext* DX11Graphics::GetImmediateContext()
		{
			return g_Instance->m_pImmediateContext;
		}

		HRESULT DX11Graphics::CreateSwapChain(DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** pSwapChain)
		{
			return g_Instance->m_pFactory->CreateSwapChain(g_Instance->m_pD3DDevice, pDesc, pSwapChain);
		}

		HRESULT DX11Graphics::CreateRenderTargetView(ID3D11Resource* pResource, D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
		{
			return GetDevice()->CreateRenderTargetView(pResource, pDesc, ppRTView);
		}

		void DX11Graphics::CreateRenderer(HWND hWnd, Value_Type** output)
		{
			(*output) = new DX11Renderer(hWnd);
		}

		void DX11Graphics::ReleaseRenderer(Value_Type** instance)
		{
			delete* instance;
			*instance = nullptr;
		}

		void LoadShaderFile(const char* filename, unsigned char** buffer, long int* fsize)
		{
			FILE* file;
			file = fopen(filename, "rb");
			*fsize = _filelength(_fileno(file));

			*buffer = new unsigned char[*fsize];
			fread(*buffer, *fsize, 1, file);
			fclose(file);
		}

		void DX11Graphics::CreateConstantBuffer()
		{
			D3D11_BUFFER_DESC desc;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = sizeof(float);

			desc.ByteWidth = sizeof(XMMATRIX);
			m_pD3DDevice->CreateBuffer(&desc, NULL, &m_ConstantBuffer[detail::CONSTANT_BUFFER_WORLD]);
			m_pD3DDevice->CreateBuffer(&desc, NULL, &m_ConstantBuffer[detail::CONSTANT_BUFFER_VIEW]);
			m_pD3DDevice->CreateBuffer(&desc, NULL, &m_ConstantBuffer[detail::CONSTANT_BUFFER_PROJECTION]);
		}

		void DX11Graphics::CreateVertexShader(const char* fileName, detail::VERTEX_INPUT_LAYOUT* inputLayout, unsigned int layoutSize)
		{
			struct VertexShader
			{
				ID3D11VertexShader* source;
				ID3D11InputLayout* layout;

				~VertexShader()
				{
					layout->Release();
					source->Release();
				}
			};
			
			VertexShader shader;
			
			long int fsize;
			unsigned char* buffer = nullptr;


			LoadShaderFile(fileName, &buffer, &fsize);

			m_pD3DDevice->CreateVertexShader(buffer,fsize,NULL,&shader.source);

			//入力レイアウト設定
			{
				D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[layoutSize];

				for (unsigned int i = 0; i < layoutSize; i++)
				{
					D3D11_INPUT_ELEMENT_DESC* target = &layout[i];
					switch (inputLayout[i])
					{
					case detail::VERTEX_INPUT_LAYOUT::VSIL_POSITION:
					{
						target->SemanticName = "POSITION";
						target->SemanticIndex = 0;
						target->Format = DXGI_FORMAT_R32G32B32_FLOAT;
						target->InputSlot = 0;
						target->AlignedByteOffset = 0;
						target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						target->InstanceDataStepRate = 0;
					}
					break;
					case detail::VERTEX_INPUT_LAYOUT::VSIL_NORMAL:
					{
						target->SemanticName = "NORMAL";
						target->SemanticIndex = 0;
						target->Format = DXGI_FORMAT_R32G32B32_FLOAT;
						target->InputSlot = 0;
						target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
						target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						target->InstanceDataStepRate = 0;
					}
					break;
					case detail::VERTEX_INPUT_LAYOUT::VSIL_COLOR:
					{
						target->SemanticName = "COLOR";
						target->SemanticIndex = 0;
						target->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						target->InputSlot = 0;
						target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
						target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						target->InstanceDataStepRate = 0;
					}
					break;
					case detail::VERTEX_INPUT_LAYOUT::VSIL_TEXCOORD:
					{
						target->SemanticName = "TEXCOORD";
						target->SemanticIndex = 0;
						target->Format = DXGI_FORMAT_R32G32_FLOAT;
						target->InputSlot = 0;
						target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
						target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						target->InstanceDataStepRate = 0;
					}
					break;
					default:
						MessageBox(NULL, "入力レイアウトの要素が欠損してます。", "エラー", MB_OK);
						break;
					}
				}

				m_pD3DDevice->CreateInputLayout(layout, layoutSize, buffer, fsize, &shader.layout);

				delete[] layout;

			}

			delete[] buffer;
		}

		void DX11Graphics::CreatePiexelShader(const char* fileName)
		{
			struct PixelShader
			{
				ID3D11PixelShader* source;

				~PixelShader()
				{
					source->Release();
				}
			};

			PixelShader shader;

			long int fsize;
			unsigned char* buffer = nullptr;

			LoadShaderFile(fileName,&buffer,&fsize);

			m_pD3DDevice->CreatePixelShader(buffer,fsize,NULL,&shader.source);

			delete[] buffer;
		}

	}// namespace ThirdParty::Platform::Graphics
}// namepsace ThirdParty::Platform