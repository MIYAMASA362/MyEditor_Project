#include"stdafx.h"

#include"Thirdparty/Graphics/DirectX11/ConstantBuffer.h"

#include"Thirdparty/Graphics/DirectX11/Transform.h"

namespace Core
{
	Transform::Transform()
	{
		m_ConstantBuffer = new Platform::Graphics::ConstantBuffer();
		m_ConstantBuffer->CreateBuffer(sizeof(Constant));
	}

	Transform::~Transform()
	{
		delete m_ConstantBuffer;
	}

	void Transform::UpdateSubResource()
	{
		m_ConstantBuffer->UpdateSubresource(&m_Constant);
	}

	void Transform::SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer)
	{
		m_ConstantBuffer->SetVSConstantBuffer(slot,numBuffer);
	}

	void Transform::SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer)
	{
		m_ConstantBuffer->SetPSConstantBuffer(slot,numBuffer);
	}

}// namespace Core