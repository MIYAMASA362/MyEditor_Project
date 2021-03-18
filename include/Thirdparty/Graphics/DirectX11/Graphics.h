#pragma once
#include <Thirdparty/Graphics/DirectX11/Shader.h>

#ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H
#define THIRDPARTY_DIRECTX11_GRAPHICS_H

/*
*	DirectX 11.h is a third party DirectX 11 wrapped header
*
*	class
*		・DX11Graphics	DirecrX11 共通グラフィックス設定
*		・DX11Renderer	DirectX11 個別グラフィックス設定
*	
* 
*/

namespace Platform
{
	namespace Graphics
	{
		/**
		* @class    DX11Graphics
		* @brief	DirectX11 共通グラフィックス設定
		*/
		class DX11Graphics final : public ::Platform::Graphics::detail::IGraphics
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

			static HRESULT CreateSwapChain(
				OUT DXGI_SWAP_CHAIN_DESC* pDesc,
				OUT IDXGISwapChain** pSwapChain
			);

			static HRESULT CreateRenderTargetView(
				IN ID3D11Resource* pResource,
				IN D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
				OUT ID3D11RenderTargetView** ppRTView
			);

		public:
			virtual void CreateRenderer(
				IN ::Platform::detail::IWindow* iWindow,
				OUT Value_Type**
			) ENGINE_OVERRIDE;

			virtual void ReleaseRenderer(
				IN Value_Type**
			) ENGINE_OVERRIDE;

			virtual void CreateVertexShader(
				IN const void* buffer,
				IN const unsigned long size,
				IN VERTEX_INPUT_LAYOUT* inputlayout,
				IN const unsigned int layoutSize, 
				OUT IVertexShader**
			) ENGINE_OVERRIDE;

			virtual void ReleaseVertexShader(
				IN IVertexShader**
			) ENGINE_OVERRIDE;

			virtual void CreatePixelShader(
				IN const void* buffer,
				IN const unsigned long size,
				OUT IPixelShader**
			) ENGINE_OVERRIDE;

			virtual void ReleasePixelShader(
				IN IPixelShader**
			) ENGINE_OVERRIDE;

			virtual void CreateConstantBuffer(
				IN unsigned int byteWidth,
				IN unsigned int byteStride,
				OUT IConstantBuffer**
			) ENGINE_OVERRIDE;

			virtual void ReleaseConstantBuffer(
				IN IConstantBuffer**
			) ENGINE_OVERRIDE;

			virtual void CreateIndexBuffer(
				IN const void* index,
				IN unsigned int size,
				IN unsigned int indexNum,
				OUT IIndexBuffer**
			) ENGINE_OVERRIDE;

			virtual void ReleaseIndexBuffer(
				IN IIndexBuffer**
			) ENGINE_OVERRIDE;

			virtual void CreateVertexBuffer(
				IN const void* vertex,
				IN unsigned int size,
				IN unsigned int vertexNum, 
				OUT IVertexBuffer**
			) ENGINE_OVERRIDE;

			virtual void ReleaseVertexBuffer(
				IN IVertexBuffer**
			) ENGINE_OVERRIDE;

			virtual void SetPrimitiveTopology(
				IN PRIMITIVE_TYPES type
			) ENGINE_OVERRIDE;

			virtual void DrawIndexed(
				IN unsigned int IndexCount,
				IN unsigned int StartIndexLocation,
				IN unsigned int BaseVertexLocation
			) ENGINE_OVERRIDE;

		};//class DX11Graphics

	}//namespace Platform::Graphics
}//namespace Platform

#endif //ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H