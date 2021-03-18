#include"Config.h"

#include"Base/Logger.h"
#include"Base/Assert.h"

#include"Base/IResource.h"

namespace Platform
{
	IResource::IResource()
		:
		m_isSecure(true)
	{

	}

	IResource::~IResource()
	{
		if (m_isSecure) LOG_ERROR("This resource has not been released");
	}

	void IResource::Release()
	{
		this->internal_release();
		m_isSecure = false;
		delete this;
	}

}// namespace Platform