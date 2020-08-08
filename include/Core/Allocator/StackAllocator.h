#pragma once
#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

namespace Core
{
	/**
	* @class    Stack Allocator
	* @brief    �X�^�b�N�A���P�[�^
	*/
	class StackAllocator : public detail::IAllocator
	{
	private:
		struct HeaderInfo
		{
			u8 adjustment;	//�p�f�B���O�T�C�Y
		};

	public:
		EXPLICIT StackAllocator(size_t size, const void* address);
		virtual ~StackAllocator();

		virtual void* allocate(size_t size, u8 alignment) override;
		virtual void free(void* memory) override;
		virtual void clear() override;

	};// class StackAllocator

	/**
	* @class    Inv StackAllocator
	* @brief    �t�X�^�b�N�A���P�[�^
	*				��ʃr�b�g���牺�ʃr�b�g�փX�^�b�N����
	*/
	class InvStackAllocator : public detail::IAllocator
	{
	private:
		struct HeaderInfo
		{
			u8 adjustment;
		};

	public:
		EXPLICIT InvStackAllocator(size_t size, const void* address);
		virtual ~InvStackAllocator();

		virtual void* allocate(size_t size, u8 alignment) override;
		virtual void free(void* memory) override;
		virtual void clear() override;

	};// class InvStackAllocator

}// namespace Core

#endif // ifndef STACKALLOCATOR_H