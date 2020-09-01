#include"Core/Common.h"
#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/PoolAllocator.h"

namespace Core
{
	PoolAllocator::PoolAllocator(size_t size, const void * memory, size_t object_size, u8 object_alignment)
		:
		IAllocator(size, memory),
		m_cObject_size(object_size),
		m_cAlignment(object_alignment)
	{
		this->Clear();
	}

	PoolAllocator::~PoolAllocator()
	{
		this->m_FreeList = nullptr;
	}

	void * PoolAllocator::Allocate(size_t size, u8 alignment)
	{
		ASSERT(size > 0, "allocate called with size = 0");
		ASSERT(size == this->m_cObject_size && alignment == this->m_cAlignment, "parameter is different from registered parameter");

		if (this->m_FreeList == nullptr) return nullptr;

		void* result = this->m_FreeList;

		this->m_FreeList = (void**)(*this->m_FreeList);

		this->m_MemoryUsed += this->m_cObject_size;
		this->m_MemoryAllocations++;

		return result;
	}

	void PoolAllocator::Free(void * p)
	{
		*((void**)p) = this->m_FreeList;

		this->m_FreeList = (void**)p;

		this->m_MemoryUsed -= this->m_cObject_size;
		this->m_MemoryAllocations--;
	}

	void PoolAllocator::Clear()
	{
		u8 adjustment = detail::GetAdjustment(this->m_MemoryFirstAddress, this->m_cAlignment);

		size_t objects = (size_t)floor((this->m_MemorySize - adjustment) / this->m_cObject_size);

		union
		{
			void* asVoidPtr;
			uptr asUptr;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;
		asUptr += this->m_MemoryUsed;

		asUptr += adjustment;

		this->m_FreeList = (void**)asVoidPtr;

		void** p = this->m_FreeList;

		for (int i = 0; i < objects - 1; ++i)
		{
			*p = (void*)((uptr)p + this->m_cObject_size);
			p = (void**)*p;
		}
		*p = nullptr;
	}

}// namespace Core
