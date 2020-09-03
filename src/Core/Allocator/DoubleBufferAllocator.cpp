#include"stdafx.h"

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
		this->Clear();
		delete this->m_StackAllocator[0];
		delete this->m_StackAllocator[1];
	}

	void * DoubleBufferAllocator::Allocate(size_t size)
	{
		return this->m_StackAllocator[this->m_CurrentStack]->Allocate(size, alignof(u8));
	}

	void DoubleBufferAllocator::Free(void * p)
	{
		this->m_StackAllocator[this->m_CurrentStack]->Free(p);
	}

	void DoubleBufferAllocator::Clear()
	{
		this->m_StackAllocator[0]->Clear();
		this->m_StackAllocator[1]->Clear();
	}

	void DoubleBufferAllocator::swapBuffers()
	{
		this->m_CurrentStack = !this->m_CurrentStack;
	}

	void DoubleBufferAllocator::clearCurrentBuffer()
	{
		this->m_StackAllocator[this->m_CurrentStack]->Clear();
	}


}// namespace Core