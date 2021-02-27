#pragma once
#ifndef PLATFORM_IBUFFER_H
#define PLATFORM_IBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{
			class ENGINE_API IBuffer : public IResource
			{
			protected:
				IBuffer() = default;
				virtual ~IBuffer() = default;

			};// class IBuffer

			class ENGINE_API IConstantBuffer : public IBuffer
			{
			protected:
				IConstantBuffer() = default;
				virtual ~IConstantBuffer() = default;

			public:
				virtual void UpdateBufferResource(const void* data) = 0;
			};

			class ENGINE_API IVertexBuffer : public IBuffer
			{
			protected:
				IVertexBuffer() = default;
				virtual ~IVertexBuffer() = default;

			public:
				virtual void SetBufferResource(unsigned int slot, unsigned int numBuffers, const unsigned int* stride, const unsigned int* offse) = 0;

			};

			class ENGINE_API IIndexBuffer : public IBuffer
			{
			protected:
				IIndexBuffer() = default;
				virtual ~IIndexBuffer() = default;

			public:
				virtual void SetBufferResource(unsigned int offset) = 0;

			};

		}// namespace Platfom::Graphics::detail
	}// namespace Platform::Graphics
}// namespace Platform

#endif // ifndef PLATFORM_IBUFFER_H