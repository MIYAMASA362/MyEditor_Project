#pragma once
#ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H
#define THIRDPARTY_DIRECTX11_INDEXBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class ENGINE_API IndexBuffer : public detail::IIndexBuffer
		{
		protected:
			ID3D11Buffer* m_Buffer;

			virtual void internal_release() override;

		public:
			IndexBuffer(const void* index, unsigned int size, unsigned int indexNum);
			virtual ~IndexBuffer();

			virtual void SetBufferResource(unsigned int offset) override;

		};// class IndexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H