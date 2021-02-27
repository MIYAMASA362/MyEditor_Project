#pragma once
#ifndef PLATFORM_IRESOURCE_H
#define PLATFORM_IRESOURCE_H

namespace Platform
{
	/**
	* @class    IResource
	* @brief    Resource Interface
	*/
	class ENGINE_API IResource
	{
	private:
		bool m_isSecure;

	protected:
		IResource() : m_isSecure(true) {};
		virtual ~IResource() { if (m_isSecure) LOG_ERROR("This resource has not been released"); };

		virtual void internal_release() = 0;

	public:
		void Release()
		{
			this->internal_release();
			m_isSecure = false;
		}

	};// class IResource

}// namespace Platform

#endif // ifndef PLATFORM_IRESOURCE_H