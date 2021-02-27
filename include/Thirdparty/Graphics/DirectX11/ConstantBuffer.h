#pragma once
#ifndef THIRDPARTY_DIRECTX11_CONSTANTBUFFER_H
#define THIRDPARTY_DIRECTX11_CONSTANTBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		/**
		* @class    ConstantBuffer
		* @brief    定数バッファ
		*
		*
		*/
		class ENGINE_API ConstantBuffer final : public detail::IConstantBuffer
		{
		protected:
			ID3D11Buffer* m_Buffer;

		protected:
			virtual void internal_release() override;

		public:
			ConstantBuffer(unsigned int byteWidth,unsigned int byteStride);
			virtual ~ConstantBuffer();

			virtual void UpdateBufferResource(const void* data) override;

			void SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);
			void SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);

		};// class ConstantBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_CONSTANTBUFFER_H