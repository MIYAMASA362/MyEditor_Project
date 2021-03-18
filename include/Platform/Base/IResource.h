#pragma once
#ifndef PLATFORM_IRESOURCE_H
#define PLATFORM_IRESOURCE_H

namespace Platform
{
	/**
	* @class    IResource
	* @brief    Resource Interface
	*/
	class IResource
	{
	protected:
		IResource() ENGINE_DEFAULT;
		virtual ~IResource() ENGINE_DEFAULT;

	public:
		virtual void Release() ENGINE_PURE;

	};// class IResource

}// namespace Platform

#endif // ifndef PLATFORM_IRESOURCE_H