#include"stdafx.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/StackAllocator.h"

namespace Core
{

	StackAllocator::StackAllocator(size_t size, const void * address)
		:
		IAllocator(size, address)
	{

	}

	StackAllocator::~StackAllocator()
	{
		this->Clear();
	}

	void * StackAllocator::Allocate(size_t size, u8 alignment)
	{
		ASSERT(size > 0, "allocate called with size = 0");

		// 共用体
		union
		{
			void* asVoidPtr;
			uptr asUptr;
		};

		// union memory
		asVoidPtr = (void*)this->m_MemoryFirstAddress;
		asUptr += this->m_MemoryUsed;
		
		// メモリ境界差分の取得
		u8 adjustment = detail::GetAdjustment(asVoidPtr, alignment, sizeof(HeaderInfo));

		// check if there is enough memory available
		if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
		{
			// not enough memory
			return nullptr;
		}

		HeaderInfo* header = (HeaderInfo*)asUptr + adjustment - sizeof(HeaderInfo);
		header->adjustment = adjustment;

		// aligned memory address
		asUptr += adjustment;


		// update book keeping
		this->m_MemoryUsed += adjustment + size;
		this->m_MemoryAllocations++;

		// return aligned memory address
		return asVoidPtr;
	}

	void StackAllocator::Free(void* memory)
	{
		ASSERT((void*)((uptr)this->m_MemoryFirstAddress + this->m_MemoryUsed) != memory, "スタックの解放順序が違います。");

		// 共用体
		union
		{
			void* asVoidPtr;
			uptr asUptr;
			HeaderInfo* asHeader;
		};

		// union memory
		asVoidPtr = memory;

		// get meta info
		asUptr -= sizeof(HeaderInfo);

		ASSERT((uptr)this->m_MemoryFirstAddress <= asUptr && asUptr <= (uptr)this->m_MemoryFirstAddress + this->m_MemorySize, "管轄外のアドレスです。");

		// free used memory
		this->m_MemoryUsed -= ((uptr)this->m_MemoryFirstAddress + this->m_MemoryUsed) - ((uptr)memory - asHeader->adjustment);

		// decrement allocation count
		this->m_MemoryAllocations--;
	}

	void StackAllocator::Clear()
	{
		// reset memory
		this->m_MemoryUsed = 0;
		this->m_MemoryAllocations = 0;
	}






	InvStackAllocator::InvStackAllocator(size_t size, const void * address)
		:
		IAllocator(size, address)
	{

	}

	InvStackAllocator::~InvStackAllocator()
	{
		this->Clear();
	}

	void * InvStackAllocator::Allocate(size_t size, u8 alignment)
	{
		ASSERT(size > 0, "allocate called with size = 0");

		union
		{
			void* asVoidPtr;
			uptr asUptr;
			HeaderInfo* header;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;

		u8 adjustment = detail::GetAdjustment(asVoidPtr, alignment, sizeof(HeaderInfo));

		if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
		{
			return nullptr;
		}

		asUptr += this->m_MemorySize - (this->m_MemoryUsed + size + adjustment);

		header->adjustment = adjustment;

		asUptr += adjustment;

		this->m_MemoryUsed += size + adjustment;
		this->m_MemoryAllocations++;

		return asVoidPtr;
	}

	void InvStackAllocator::Free(void * memory)
	{
		union
		{
			void* asVoidPtr;
			uptr asUptr;
			HeaderInfo* header;
		};

		asVoidPtr = memory;

		asUptr -= sizeof(HeaderInfo);

		this->m_MemoryUsed -= ((uptr)this->m_MemoryFirstAddress + this->m_MemorySize - this->m_MemoryUsed) - ((uptr)memory - header->adjustment);
		this->m_MemoryAllocations--;
	}

	void InvStackAllocator::Clear()
	{
		this->m_MemoryUsed = 0;
		this->m_MemoryFirstAddress = 0;
	}

}// namespace Core