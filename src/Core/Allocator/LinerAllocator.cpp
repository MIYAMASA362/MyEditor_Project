#include"Core/Common.h"
#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/LinerAllocator.h"

namespace Core
{

	LinerAllocator::LinerAllocator(size_t size, const void * memory)
		:
		IAllocator(size, memory)
	{

	}

	LinerAllocator::~LinerAllocator()
	{
		this->clear();
	}

	void * LinerAllocator::allocate(size_t size, u8 alignment)
	{
		ASSERT(size > 0, "allocate called with memsize = 0");

		union
		{
			void* asVoidPtr;
			uptr asUptr;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;
		asUptr += this->m_MemoryUsed;

		u8 adjustment = detail::GetAdjustment(asVoidPtr, alignment);

		if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
		{
			return nullptr;
		}

		asUptr += adjustment;

		this->m_MemoryUsed += size + adjustment;
		this->m_MemoryAllocations++;

		return asVoidPtr;
	}

	void LinerAllocator::free(void * p)
	{
		ASSERT(false, "Liner allocator do not support free operations, Use clear instead");
	}

	void LinerAllocator::clear()
	{
		this->m_MemoryUsed = 0;
		this->m_MemoryAllocations = 0;
	}


}// namespace Core