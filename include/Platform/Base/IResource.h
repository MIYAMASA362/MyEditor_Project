#pragma once
#ifndef PLATFORM_RESOURCE_H
#define PLATFORM_RESOURCE_H

namespace Platform
{
	/**
	* @class    IResource
	* @brief    ���\�[�X�C���^�[�t�F�C�X
	*/
	class IResource
	{
	public:
		virtual void Release() ENGINE_PURE;

	protected:
		IResource();
		virtual ~IResource();

	};// class IResource

}// namespace Platform

#endif // ifndef PLATFORM_RESOURCE_H