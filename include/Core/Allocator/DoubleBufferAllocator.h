#pragma once
#ifndef DOUBLEBUFFERALLOCATOR_H
#define DOUBLEBUFFERALLOCATOR_H

namespace Core
{
	/**
	* @class    DoubleBufferAllocator
	* @brief	二重バッファアロケータ
	*			this allocator sported stackallocator
	*/
	class DoubleBufferAllocator
	{
	private:
		u32 m_CurrentStack;

		StackAllocator* m_StackAllocator[2];

	public:
		EXPLICIT DoubleBufferAllocator(size_t size, const void* address);
		virtual ~DoubleBufferAllocator();

		void* allocate(size_t size);
		void free(void* p);
		void clear();

		void swapBuffers();
		void clearCurrentBuffer();

	};// class DobuleBufferAllocator

}// namespace Core

#endif // ifndef DOUBLEBUFFERALLOCATOR_H