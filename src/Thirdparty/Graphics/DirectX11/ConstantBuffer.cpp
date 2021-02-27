#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include"Thirdparty/Graphics/DirectX11/ConstantBuffer.h"

namespace Platform
{
	namespace Graphics
	{
		void ConstantBuffer::internal_release()
		{
			if (m_Buffer == nullptr) return;
			m_Buffer->Release();
			delete m_Buffer;
		}

		ConstantBuffer::ConstantBuffer(unsigned int byteWidth, unsigned int byteStride)
			:
			m_Buffer(nullptr)
		{
			D3D11_BUFFER_DESC desc;
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = 0;
				desc.MiscFlags = 0;
				desc.StructureByteStride = byteStride;
				desc.ByteWidth = byteWidth;
			}

			DX11Graphics::GetDevice()->CreateBuffer(&desc, NULL, &m_Buffer);
		}

		ConstantBuffer::~ConstantBuffer()
		{
			
		}

		void ConstantBuffer::UpdateBufferResource(const void* data)
		{
			DX11Graphics::GetImmediateContext()->UpdateSubresource(m_Buffer,0,NULL,data,0,0);
		}

		void ConstantBuffer::SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer)
		{
			DX11Graphics::GetImmediateContext()->VSSetConstantBuffers(slot,numBuffer,&m_Buffer);
		}

		void ConstantBuffer::SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer)
		{
			DX11Graphics::GetImmediateContext()->PSSetConstantBuffers(slot,numBuffer,&m_Buffer);
		}

	}// namespace Platform::Graphics
}// namespace Platform