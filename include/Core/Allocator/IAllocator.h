#pragma once
#ifndef IALLOCATOR_H
#define IALLOCATOR_H

namespace Core
{
	namespace detail
	{
		/*
		*	AlignForward
		*		�o�C�g���E�����ς� �A�h���X
		*
		*/
		static inline void* AlignForward(void* address, u8 alignment)
		{
			return (void*)((reinterpret_cast<uptr>(address) + static_cast<u8>(alignment - 1)) & static_cast<u8>(~(alignment - 1)));
		}

		/*
		*	GetAjustment
		*		�o�C�g���E �����l
		*
		*		address		:	�擪�A�h���X
		*		alignment	:	�A���C�����g�l
		*/
		static inline u8 GetAdjustment(const void* address, u8 alignment)
		{
			u8 adjustment = alignment - (reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment - 1));

			return adjustment == alignment ? 0 : adjustment;
		}

		/*
		*	GetAjustment
		*		�o�C�g���E �����l
		*
		*		address		:	�擪�A�h���X
		*		alignment	:	�A���C�����g�l
		*		header		:	Header���
		*/
		static inline u8 GetAdjustment(const void* address, u8 alignment, u8 header)
		{
			u8 adjustment = GetAdjustment(address, alignment);

			u8 needSpace = header;

			// �p�f�B���O�̈����info�����܂邩
			if (adjustment < needSpace)
			{
				needSpace -= adjustment;

				adjustment += alignment * (needSpace / alignment);

				if (needSpace % alignment > 0) adjustment += alignment;
			}

			return adjustment;
		}

		/**
		* @class    IAllocator
		* @brief    Allocator intarface
		*/
		class IAllocator
		{
		protected:
			const size_t	m_MemorySize;				//�������T�C�Y
			const void*		m_MemoryFirstAddress;		//�������擪�A�h���X

			size_t			m_MemoryUsed;				//�������̗��p��
			uint64_t		m_MemoryAllocations;		//�������A���P�[�V������

		public:
			EXPLICIT IAllocator(const size_t size, const void* memory)
				:
				m_MemorySize(size),
				m_MemoryFirstAddress(memory),
				m_MemoryUsed(0),
				m_MemoryAllocations(0)
			{}
			virtual ~IAllocator() 
			{}

			virtual void* Allocate(size_t size, uint8_t alignment) =0;
			virtual void Free(void* p) =0;
			virtual void Clear() =0;

			/*
			*	Acceser
			*
			*/
			//! �������T�C�Y
			inline size_t GetMemorySize() const
			{
				return this->m_MemorySize;
			}
			//! �������擪�A�h���X
			inline const void* GetFirstAddress() const
			{
				return this->m_MemoryFirstAddress;
			}

			//! �������̗��p��
			inline size_t GetMemoryUsed() const
			{
				return this->m_MemoryUsed;
			}
			//! �A���P�[�V������
			inline uint64_t GetAllocationCount() const
			{
				return this->m_MemoryAllocations;
			}

		};// class IAllocator

	}// namespace Core::detail

}// namespace Core

#endif //ifndef IALLOCATOR_H
