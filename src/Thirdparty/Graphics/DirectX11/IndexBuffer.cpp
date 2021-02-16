#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include"Thirdparty/Graphics/DirectX11/IBuffer.h"
#include"Thirdparty/Graphics/DirectX11/IndexBuffer.h"

namespace Platform
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer()
		{

		}
		
		IndexBuffer::~IndexBuffer()
		{

		}

		void IndexBuffer::CreateBuffer(const void* index, unsigned int size, unsigned int indexNum)
		{
			D3D11_BUFFER_DESC desc;
			{
				desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.CPUAccessFlags = 0;
				desc.ByteWidth = size * indexNum;
			}

			D3D11_SUBRESOURCE_DATA sd;
			{
				sd.pSysMem = index;
				sd.SysMemPitch = 0;
				sd.SysMemSlicePitch = 0;
			}

			DX11Graphics::GetDevice()->CreateBuffer(&desc,&sd,&m_Buffer);
		}

		void IndexBuffer::SetBuffer(unsigned int offset)
		{
			DX11Graphics::GetImmediateContext()->IASetIndexBuffer(m_Buffer, DXGI_FORMAT_R32_UINT, offset);
		}

	}// namespace Platform::Graphics
}// namespace Platform