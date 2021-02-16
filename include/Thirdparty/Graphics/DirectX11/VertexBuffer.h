#pragma once
#ifndef THIRDPARTY_DIRECTX11_VERTEXBUFFER_H
#define THIRDPARTY_DIRECTX11_VERTEXBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class ENGINE_API VertexBuffer : public IBuffer
		{
		public:
			VertexBuffer();
			virtual ~VertexBuffer();

			void CreateBuffer(const void* vertex,unsigned int size, unsigned int vertexNum);
			void SetBuffer(unsigned int slot, unsigned int numBuffers, const unsigned int* stride, const unsigned int* offset);

		};// class VertexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_VERTEXBUFFER_H