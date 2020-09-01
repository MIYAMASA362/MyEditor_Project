#pragma once
#ifndef LINERALLOCATOR_H
#define LINERALLOCATOR_H

namespace Core
{
	/**
	* @class    LinerAllocator
	* @brief
	*/
	class LinerAllocator : public detail::IAllocator
	{
	private:

	public:

		EXPLICIT LinerAllocator(size_t size, const void * memory);
		virtual ~LinerAllocator();

		virtual void* Allocate(size_t size, u8 alignment) override;
		virtual void Free(void* p) override;
		virtual void Clear() override;
	}; //class LinerAllocator

}// namespace Core

#endif // ifndef LINERALLOCATOR_H