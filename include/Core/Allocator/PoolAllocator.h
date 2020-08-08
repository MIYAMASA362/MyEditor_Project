#pragma once
#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

namespace Core
{
	/**
	* @class    PoolAllocator
	* @brief    Enum Description
	*/
	class PoolAllocator : public detail::IAllocator
	{
	private:

		const size_t	m_cObject_size;
		const u8		m_cAlignment;

		void**			m_FreeList;
	public:

		EXPLICIT PoolAllocator(size_t size, const void* memory, size_t object_size, u8 alignment);
		virtual ~PoolAllocator();

		virtual void* allocate(size_t size, u8 alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;

	};// class PoolAllocator

}// namespace Core

#endif // ifndef POOLALLOCATOR_H