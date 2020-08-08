#include"Core/Base/Common.h"
#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/StackAllocator.h"
#include"Core/Allocator/DoubleBufferAllocator.h"

namespace Core
{

	DoubleBufferAllocator::DoubleBufferAllocator(size_t size, const void * address)
		:
		m_CurrentStack(0)
	{
		this->m_StackAllocator[0] = new StackAllocator(size, address);
		this->m_StackAllocator[1] = new StackAllocator(size, (void*)((uptr)address + size + detail::GetAdjustment((void*)((uptr)address + size + 1), alignof(u8))));
	}

	DoubleBufferAllocator::~DoubleBufferAllocator()
	{
		this->clear();
		delete this->m_StackAllocator[0];
		delete this->m_StackAllocator[1];
	}

	void * DoubleBufferAllocator::allocate(size_t size)
	{
		return this->m_StackAllocator[this->m_CurrentStack]->allocate(size, alignof(u8));
	}

	void DoubleBufferAllocator::free(void * p)
	{
		this->m_StackAllocator[this->m_CurrentStack]->free(p);
	}

	void DoubleBufferAllocator::clear()
	{
		this->m_StackAllocator[0]->clear();
		this->m_StackAllocator[1]->clear();
	}

	void DoubleBufferAllocator::swapBuffers()
	{
		this->m_CurrentStack = !this->m_CurrentStack;
	}

	void DoubleBufferAllocator::clearCurrentBuffer()
	{
		this->m_StackAllocator[this->m_CurrentStack]->clear();
	}


}// namespace Core