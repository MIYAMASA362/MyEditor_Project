#pragma once
#ifndef PLATFORM_REFOBJECT_H
#define PLATFORM_REFOBJECT_H

namespace Platform
{
	/**
	* @class    RefObject
	* @brief    参照オブジェクト
	*
	*	参照カウンタ方式
	*
	*
	*/
	class RefObject
	{
	protected:
		RefObject();
		virtual ~RefObject();

	private:
		RefObject(const RefObject&) = delete;

		mutable u32 m_RefCount;
		u32 m_Flags;

		u32 retain();
		void release();

		friend class RefHelper;

	public:
		RefObject& operator=(RefObject&);

	};// class RefObject

	class RefHelper
	{
	public:
		static void retain(RefObject* obj) {
			obj->retain();
		}

		static void release(RefObject* obj) {
			obj->release();
		}

	};// class RefHelper

	/**
	* @class    Ref
	* @brief
	*/
	template<class Type>
	class Ref
	{
	private:
		Type* m_Ptr;

	public:
		Ref() : m_Ptr(new Type()) {};

		Type* ptr() noexcept { return m_Ptr; }

	};// class Ref

}// namespace Platform

#endif // ifndef PLATFORM_REFOBJECT_H