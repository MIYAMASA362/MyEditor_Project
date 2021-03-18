#pragma once
#ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H
#define THIRDPARTY_DIRECTX11_INDEXBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class IndexBuffer : public IIndexBuffer
		{
		protected:
			ID3D11Buffer* m_Buffer;

		public:
			IndexBuffer(const void* index, unsigned int size, unsigned int indexNum);
			virtual ~IndexBuffer();

			virtual void SetBufferResource(unsigned int offset) override;

			virtual void Release() override;

		};// class IndexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H