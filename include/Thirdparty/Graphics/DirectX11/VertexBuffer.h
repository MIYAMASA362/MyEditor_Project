#pragma once
#ifndef THIRDPARTY_DIRECTX11_VERTEXBUFFER_H
#define THIRDPARTY_DIRECTX11_VERTEXBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class VertexBuffer : public IVertexBuffer
		{
		protected:
			ID3D11Buffer* m_Buffer;

		public:
			VertexBuffer(const void* vertex, unsigned int size, unsigned int vertexNum);
			virtual ~VertexBuffer();

			virtual void SetBufferResource(unsigned int slot, unsigned int numBuffers, const unsigned int* stride, const unsigned int* offset) override;

			virtual void Release() override;

		};// class VertexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_VERTEXBUFFER_H