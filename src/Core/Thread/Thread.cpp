#include "stdafx.h"
#include "Core/Thread/Thread.h"

namespace Core
{
	Thread::~Thread()
	{
		
	}

	void Thread::run()
	{
		m_Worker.join();
	}

}// namespace Core