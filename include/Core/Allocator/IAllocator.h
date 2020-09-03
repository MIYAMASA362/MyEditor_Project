#pragma once
#ifndef IALLOCATOR_H
#define IALLOCATOR_H

namespace Core
{
	namespace detail
	{
		/*
		*	AlignForward
		*		バイト境界調整済み アドレス
		*
		*/
		static inline void* AlignForward(void* address, u8 alignment)
		{
			return (void*)((reinterpret_cast<uptr>(address) + static_cast<u8>(alignment - 1)) & static_cast<u8>(~(alignment - 1)));
		}

		/*
		*	GetAjustment
		*		バイト境界 調整値
		*
		*		address		:	先頭アドレス
		*		alignment	:	アライメント値
		*/
		static inline u8 GetAdjustment(const void* address, u8 alignment)
		{
			u8 adjustment = alignment - (reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment - 1));

			return adjustment == alignment ? 0 : adjustment;
		}

		/*
		*	GetAjustment
		*		バイト境界 調整値
		*
		*		address		:	先頭アドレス
		*		alignment	:	アライメント値
		*		header		:	Header情報
		*/
		static inline u8 GetAdjustment(const void* address, u8 alignment, u8 header)
		{
			u8 adjustment = GetAdjustment(address, alignment);

			u8 needSpace = header;

			// パディング領域内にinfoが収まるか
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
			const size_t	m_MemorySize;				//メモリサイズ
			const void*		m_MemoryFirstAddress;		//メモリ先頭アドレス

			size_t			m_MemoryUsed;				//メモリの利用数
			uint64_t		m_MemoryAllocations;		//メモリアロケーション数

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
			//! メモリサイズ
			inline size_t GetMemorySize() const
			{
				return this->m_MemorySize;
			}
			//! メモリ先頭アドレス
			inline const void* GetFirstAddress() const
			{
				return this->m_MemoryFirstAddress;
			}

			//! メモリの利用数
			inline size_t GetMemoryUsed() const
			{
				return this->m_MemoryUsed;
			}
			//! アロケーション数
			inline uint64_t GetAllocationCount() const
			{
				return this->m_MemoryAllocations;
			}

		};// class IAllocator

	}// namespace Core::detail

}// namespace Core

#endif //ifndef IALLOCATOR_H
