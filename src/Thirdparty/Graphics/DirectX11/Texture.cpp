#include "stdafx.h"

#include"Thirdparty/Graphics/DirectX11/Texture.h"

#include"Thirdparty/Graphics/DirectX11/Graphics.h"

namespace Platform
{
	namespace Graphics
	{
		namespace Textures
		{
			Texture::Texture()
				:
				m_Source(nullptr),
				m_SRV(nullptr)
			{
			
			}
			Texture::~Texture()
			{
				if (m_SRV) m_SRV->Release();
				if (m_Source) m_Source->Release();
			}


			void Texture::LoadTexture(const void* pixels, unsigned int width, unsigned int height, unsigned int bpp)
			{
				HRESULT hr;

				D3D11_TEXTURE2D_DESC desc;
				{
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.Usage = D3D11_USAGE_DEFAULT;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					desc.SampleDesc.Count = 1;
					desc.SampleDesc.Quality = 0;

					desc.MipLevels = 1;
					desc.ArraySize = 1;
					desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					desc.Width = width;
					desc.Height = height;
				}

				D3D11_SUBRESOURCE_DATA sd;
				{
					sd.pSysMem = pixels;
					sd.SysMemPitch = width * 4;
					sd.SysMemSlicePitch = width * height * bpp;
				}

				hr = DX11Graphics::GetDevice()->CreateTexture2D(&desc,&sd,&m_Source);
				ASSERT(SUCCEEDED(hr),"テクスチャの生成に失敗しました。");

				D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
				{
					srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
					srv.Texture2D.MipLevels = 1;
				}

				hr = DX11Graphics::GetDevice()->CreateShaderResourceView(m_Source,&srv,&m_SRV);
				ASSERT(SUCCEEDED(hr),"テクスチャのシェーダリソースの生成に失敗しました。");
			}

			void Texture::SetResource(unsigned int slot, unsigned int view)
			{
				DX11Graphics::GetImmediateContext()->PSSetShaderResources(slot,view,&m_SRV);
			}

		}// namespace Platform::Graphics::Textures
	}// namespace Platform::Graphics
}// namespace Platform