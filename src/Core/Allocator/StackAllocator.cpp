#include"Core/Common.h"
#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"

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
		this->clear();
	}

	void * StackAllocator::allocate(size_t size, u8 alignment)
	{
		ASSERT(size > 0, "allocate called with size = 0");

		// ���p��
		union
		{
			void* asVoidPtr;
			uptr asUptr;
			HeaderInfo* asHeader;
		};

		// union memory
		asVoidPtr = (void*)this->m_MemoryFirstAddress;
		asUptr += this->m_MemoryUsed;

		// ���������E�����̎擾
		u8 adjustment = detail::GetAdjustment(asVoidPtr, alignment, sizeof(HeaderInfo));

		// check if there is enough memory available
		if (this->m_MemoryUsed + size + adjustment > this->m_MemorySize)
		{
			// not enough memory
			return nullptr;
		}

		// store alignment in allocation header info
		asHeader->adjustment = adjustment;

		// aligned memory address
		asUptr += adjustment;

		// update book keeping
		this->m_MemoryUsed += size + adjustment;
		this->m_MemoryAllocations++;

		// return aligned memory address
		return asVoidPtr;
	}

	void StackAllocator::free(void* memory)
	{
		ASSERT((void*)((uptr)this->m_MemoryFirstAddress + this->m_MemoryUsed) != memory, "�X�^�b�N�̉���������Ⴂ�܂��B");

		// ���p��
		union
		{
			void* asVoidPtr;
			uptr asUptr;
			HeaderInfo* asMeta;
		};

		// union memory
		asVoidPtr = memory;

		// get meta info
		asUptr -= sizeof(HeaderInfo);

		ASSERT((uptr)this->m_MemoryFirstAddress <= asUptr && asUptr <= (uptr)this->m_MemoryFirstAddress + this->m_MemorySize, "�Ǌ��O�̃A�h���X�ł��B");

		// free used memory
		this->m_MemoryUsed -= ((uptr)this->m_MemoryFirstAddress + this->m_MemoryUsed) - ((uptr)memory + asMeta->adjustment);

		// decrement allocation count
		this->m_MemoryAllocations--;
	}

	void StackAllocator::clear()
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
		this->clear();
	}

	void * InvStackAllocator::allocate(size_t size, u8 alignment)
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

	void InvStackAllocator::free(void * memory)
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

	void InvStackAllocator::clear()
	{
		this->m_MemoryUsed = 0;
		this->m_MemoryFirstAddress = 0;
	}

}// namespace Core