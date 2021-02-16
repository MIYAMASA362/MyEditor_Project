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
		*	Stride : float
		*
		*/
		class ENGINE_API ConstantBuffer final : public IBuffer
		{
		public:
			ConstantBuffer();
			virtual ~ConstantBuffer();

			void CreateBuffer(unsigned int size);
			void UpdateSubresource(const void* data);

			void SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);
			void SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);

		};// class ConstantBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_CONSTANTBUFFER_H