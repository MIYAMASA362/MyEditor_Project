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
		class ConstantBuffer;

		/**
		* @class    DX11Graphics
		* @brief	DirectX11 共通グラフィックス設定
		*/
		class ENGINE_API DX11Graphics final : public ::Platform::Graphics::detail::IGraphics
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

			static HRESULT CreateSwapChain(DXGI_SWAP_CHAIN_DESC* pDesc,IDXGISwapChain** pSwapChain);
			static HRESULT CreateRenderTargetView(ID3D11Resource* pResource,D3D11_RENDER_TARGET_VIEW_DESC* pDesc,ID3D11RenderTargetView** ppRTView);

		public:
			virtual void CreateRenderer(::Platform::detail::IWindow* iWindow, Value_Type** output) override;
			virtual void ReleaseRenderer(Value_Type** instance) override;

			virtual void CreateVertexShader(const void* buffer, const unsigned long size, VERTEX_INPUT_LAYOUT* inputlayout, const unsigned int layoutSize, detail::IShader** output) override;
			virtual void ReleaseVertexShader(detail::IShader** instance) override;

			virtual void CreatePixelShader(const void* buffer, const unsigned long size, detail::IShader** output) override;
			virtual void ReleasePixelShader(detail::IShader** instance) override;

			virtual void CreateConstantBuffer(unsigned int byteWidth, unsigned int byteStride, detail::IConstantBuffer** output) override;

			virtual void CreateIndexBuffer(const void* index, unsigned int size, unsigned int indexNum, detail::IIndexBuffer** output) override;

			virtual void CreateVertexBuffer(const void* vertex, unsigned int size, unsigned int vertexNum,detail::IVertexBuffer** output) override;

		};//class DX11Graphics

	}//namespace Platform::Graphics
}//namespace Platform

#endif //ifndef THIRDPARTY_DIRECTX11_GRAPHICS_H