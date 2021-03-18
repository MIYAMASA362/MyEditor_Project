#pragma once
#ifndef PLATFORM_IBUFFER_H
#define PLATFORM_IBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{

			/**
			* @class    IBuffer
			* @brief    バッファ
			*/
			class IBuffer : public IResource
			{
			protected:
				IBuffer() ENGINE_DEFAULT;
				virtual ~IBuffer() ENGINE_DEFAULT;

			};// class IBuffer

		}// namespace Platform::Graphics::detail

		/**
		* @class    IConstantBufffer
		* @brief    ConstantBuffer Interface
		*/
		class IConstantBuffer : public detail::IBuffer
		{
		protected:
			IConstantBuffer() ENGINE_DEFAULT;
			virtual ~IConstantBuffer() ENGINE_DEFAULT;

		public:
			virtual void UpdateBufferResource(
				IN const void* data
			) ENGINE_PURE;

		};// class IConstantBuffer


		/**
		* @class    IVertexBuffer
		* @brief    VertexBuffer Interface
		*/
		class IVertexBuffer : public detail::IBuffer
		{
		protected:
			IVertexBuffer() ENGINE_DEFAULT;
			virtual ~IVertexBuffer() ENGINE_DEFAULT;

		public:
			virtual void SetBufferResource(
				IN unsigned int slot,
				IN unsigned int numBuffers,
				IN const unsigned int* stride,
				IN const unsigned int* offse
			) ENGINE_PURE;

		};// class IVertexBuffer


		/**
		* @class    IIndexBuffer
		* @brief    IndexBuffer Interface
		*/
		class IIndexBuffer : public detail::IBuffer
		{
		protected:
			IIndexBuffer() ENGINE_DEFAULT;
			virtual ~IIndexBuffer() ENGINE_DEFAULT;

		public:
			virtual void SetBufferResource(
				IN unsigned int offset
			) ENGINE_PURE;

		};// class IIndexBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif // ifndef PLATFORM_IBUFFER_H