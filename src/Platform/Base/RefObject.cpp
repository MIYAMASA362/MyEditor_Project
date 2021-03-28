#include"Config.h"

#include"Base/Logger.h"

#include"Base/RefObject.h"

namespace Platform
{
	/*
	RefObject& RefObject::operator=(RefObject& obj)
	{
		RefHelper::retain(this);
		return *this;
	}
	
	u32 RefObject::retain()
	{
		LOG_DEBUG("Called retain");
		m_RefCount++;
		return m_RefCount;
	}

	void RefObject::release()
	{
		LOG_DEBUG("Called releasse");
		m_RefCount--;
		if (m_RefCount <= 0) delete this;
	}*/

}// namespace Platform