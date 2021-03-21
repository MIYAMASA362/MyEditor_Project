#pragma once
#ifndef CORE_TASK_H
#define CORE_TASK_H

namespace Core
{
	/**
	* @brief    Task of State
	*/
	enum class TaskState
	{
		None,
		Running,
		Finished,
		Canceled,
	};

	namespace detail
	{
		/**
		* @class    ITask
		* @brief    Task Interface
		*/
		class ITask
		{
		public:
			virtual void run() = 0;
			virtual void cancel() = 0;

			virtual TaskState GetState() const;
		protected:
			ITask();
			virtual ~ITask();

			TaskState m_TaskState;

		};// class ITask

	}// namespace detail
}// namespace Core


#endif // ifndef CORE_TASK_H