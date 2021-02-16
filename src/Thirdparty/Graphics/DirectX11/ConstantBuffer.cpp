#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include"Thirdparty/Graphics/DirectX11/IBuffer.h"
#include"Thirdparty/Graphics/DirectX11/ConstantBuffer.h"

namespace Platform
{
	namespace Graphics
	{
		ConstantBuffer::ConstantBuffer()
		{

		}

		ConstantBuffer::~ConstantBuffer()
		{
			if (m_Buffer) delete m_Buffer;
		}

		void ConstantBuffer::CreateBuffer(unsigned int size)
		{
			D3D11_BUFFER_DESC desc;
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = 0;
				desc.MiscFlags = 0;
				desc.StructureByteStride = sizeof(float);
				desc.ByteWidth = size;
			}

			DX11Graphics::GetDevice()->CreateBuffer(&desc,NULL,&m_Buffer);
		}

		void ConstantBuffer::UpdateSubresource(const void* data)
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