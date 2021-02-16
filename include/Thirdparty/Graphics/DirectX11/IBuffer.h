#pragma once
#ifndef THIRDPARTY_DIRECTX11_IBUFFER_H
#define THIRDPARTY_DIRECTX11_IBUFFER_H

namespace Platform
{
	namespace Graphics
	{
		class IBuffer 
		{
		protected:
			ID3D11Buffer* m_Buffer;

		public:
			IBuffer();
			virtual ~IBuffer();

		};// class IBuffer

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef THIRDPARTY_DIRECTX11_IBUFFER_Hs