#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include"Thirdparty/Graphics/DirectX11/VertexBuffer.h"

namespace Platform
{
	namespace Graphics
	{

		VertexBuffer::VertexBuffer(const void* vertex, unsigned int size, unsigned int vertexNum)
			:
			m_Buffer(nullptr)
		{
			D3D11_BUFFER_DESC desc;
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				desc.CPUAccessFlags = 0;
				desc.ByteWidth = size * vertexNum;
			}

			D3D11_SUBRESOURCE_DATA sd;
			{
				sd.pSysMem = vertex;
				sd.SysMemPitch = 0;
				sd.SysMemSlicePitch = 0;
			}

			DX11Graphics::GetDevice()->CreateBuffer(&desc, &sd, &m_Buffer);
		}
		VertexBuffer::~VertexBuffer()
		{
			ASSERT(m_Buffer != nullptr,"リソースの解放がされていません。");
		}

		void VertexBuffer::SetBufferResource(unsigned int slot, unsigned int numBuffers, const unsigned int* stride, const unsigned int* offset)
		{
			DX11Graphics::GetImmediateContext()->IASetVertexBuffers(slot,numBuffers,&m_Buffer,stride,offset);
		}

		void VertexBuffer::Release()
		{
			if (m_Buffer) m_Buffer->Release();
		}

	}// namespace Platform::Graphics
}// namespace Platform