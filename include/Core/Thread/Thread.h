#pragma once
#ifndef CORE_THREAD_H
#define CORE_THREAD_H

#include <thread>
#include <atomic>
#include <process.h>

namespace Core {
	namespace detail {

		/* @bried Thread Handle */
		using ThreadHandle = HANDLE;

		/**
		* @class    IThread
		* @brief    Thread Interface
		*/
		class IThread
		{
		public:
			// Thread Run
			virtual void run() = 0;
		
		protected:
			IThread() {};
			virtual ~IThread() {};

		};// class IThread

		/**
		* @class    Thread_guard
		* @brief    
		*/
		class Thread_guard final
		{
		public:
			explicit Thread_guard(std::thread& t) :m_thread(t) {}
			~Thread_guard()
			{
				if (m_thread.joinable())
					m_thread.detach();
			}

			Thread_guard(Thread_guard const &) = delete;
			Thread_guard& operator=(Thread_guard const &) = delete;

		private:
			std::thread& m_thread;

		};// class Thread_guard

	}
}// namespace Core::detail

namespace Core
{
	/* Hardware Processer Num  */
	static inline unsigned int GetThread_Concurrency()
	{
		return std::thread::hardware_concurrency();
	}

	/**
	* @class    Thread
	* @brief
	*/
	class Thread : public detail::IThread
	{
	public:
		template<class F, class ...Args>
		Thread(F&& f, Args&& ...args);
		virtual ~Thread();

		virtual void run() override;

	protected:
		std::thread m_Worker;
	
	private:
		detail::Thread_guard m_Guard;

	};// class Thread

	template<class F, class ...Args>
	inline Thread::Thread(F && f, Args && ...args)
		:
		m_Worker(f, std::forward<Args>(args)...),
		m_Guard(m_Worker)
	{

	}

}// namespace Core

#endif// ifndef CORE_THREAD_H