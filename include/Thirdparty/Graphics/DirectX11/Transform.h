#pragma once
#ifndef THIRDPARTY_DIRECTX11_TRANSFORM_H
#define THIRDPARTY_DIRECTX11_TRANSFORM_H

namespace Core
{

	/**
	* @class    Transform
	* @brief    çsóÒïœä∑
	*/
	class ENGINE_API Transform
	{
	private:
		Platform::Graphics::ConstantBuffer* m_ConstantBuffer;

	public:
		struct Constant
		{
			XMMATRIX worldMatrix;
			XMMATRIX viewMatrix;
			XMMATRIX projectMatrix;
		};

		Constant m_Constant;

	public:
		Transform();
		virtual ~Transform();

		void UpdateSubResource();

		void SetVSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);
		void SetPSConstantBuffer(unsigned int slot, unsigned int numBuffer = 1);

	};// class Transform

}// namespace Core

#endif // ifndef THIRDPARTY_DIRECTX11_TRANSFORM_H