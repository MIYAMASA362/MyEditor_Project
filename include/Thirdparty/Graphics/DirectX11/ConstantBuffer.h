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
		class ConstantBuffer final : public IConstantBuffer
		{
		protected:
			ID3D11Buffer* m_Buffer;

		public:
			ConstantBuffer(unsigned int byteWidth,unsigned int byteStride);
			virtual ~ConstantBuffer();

			virtual void UpdateBufferResource(const void* data) override;

			void SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);
			void SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);

			virtual void Release() override;

		};// class ConstantBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_CONSTANTBUFFER_H