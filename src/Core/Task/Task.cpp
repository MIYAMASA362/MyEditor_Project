#include"Config.h"
#include"Core/Thread/Task.h"

namespace Core
{
	TaskState detail::ITask::GetState() const
	{
		return m_TaskState;
	}

	detail::ITask::ITask()
		:
		m_TaskState(TaskState::None)
	{

	}

	detail::ITask::~ITask()
	{

	}

}// namespace Core
