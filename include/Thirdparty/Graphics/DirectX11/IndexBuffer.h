#pragma once
#ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H
#define THIRDPARTY_DIRECTX11_INDEXBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class ENGINE_API IndexBuffer : public IBuffer
		{
		public:
			IndexBuffer();
			virtual ~IndexBuffer();

			void CreateBuffer(const void* index,unsigned int size,unsigned int indexNum);
			void SetBuffer(unsigned int offset);

		};// class IndexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_INDEXBUFFER_H