#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Thirdparty/Graphics/DirectX11/IBuffer.h"

namespace Platform
{
	namespace Graphics
	{
		IBuffer::IBuffer()
			:
			m_Buffer(nullptr)
		{

		}
		IBuffer::~IBuffer()
		{
			if (m_Buffer) m_Buffer->Release();
		}


	}// namespace Platform::Graphics
}// namespace Platform