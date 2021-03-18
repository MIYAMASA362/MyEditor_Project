#include"Config.h"

#include"Base/Logger.h"

#include"Base/RefObject.h"

namespace Platform
{
	RefObject::RefObject()
		:
		m_RefCount(1),
		m_Flags(1)
	{

	}

	RefObject::~RefObject()
	{
		if(m_RefCount > 1)
		{
			LOG_ERROR("参照カウントが1以上です。");
		}
	}

	RefObject& RefObject::operator=(RefObject& obj)
	{
		RefHelper::retain(this);
		RefHelper::release(&obj);
		return *this;
	}
	
	u32 RefObject::retain()
	{
		m_RefCount++;
		return m_RefCount;
	}

	void RefObject::release()
	{
		m_RefCount--;
		if (m_RefCount <= 0) delete this;
	}

}// namespace Platform