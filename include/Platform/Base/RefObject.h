#pragma once
#ifndef PLATFORM_REFOBJECT_H
#define PLATFORM_REFOBJECT_H

namespace Platform
{
	class RefObject
	{
	public:

	protected:
		RefObject() = default;
		virtual ~RefObject() = default;

	private:
		mutable u32 m_RefCount;

	};// class RefObject

	/**
	* @class	Ref
	* @brief	参照ポインタ
	*/
	template<class T>
	class Ref
	{
		template<class T,class... Args>
	 	friend static void CreateRef(Ref<T>& target, Args... args);
	public:
		Ref();
		virtual ~Ref();

		void Release();
		void Swap(Ref<T>& obj);

		T* operator->() const noexcept;


	private:
		T* m_Source;

	};// class Ref

	template<class T>
	Ref<T>::Ref()
		:
		m_Source(nullptr)
	{
		
	}

	template<class T>
	Ref<T>::~Ref()
	{
		if (m_Source != nullptr) {
			delete m_Source;
			m_Source = nullptr;
		}
	}

	template<class T>
	T* Ref<T>::operator->() const noexcept
	{
		return m_Source;
	}

	template<class T>
	void Ref<T>::Release()
	{
		delete m_Source;
		m_Source = nullptr;
	}

	template<class T>
	void Ref<T>::Swap(Ref<T>& obj)
	{
		delete m_Source;
		m_Source = obj.m_Source;
	}

	template<class T,class... Args>
	static void CreateRef(Ref<T>& target, Args... args) 
	{
		target.m_Source = new T(std::forward<Args>(args)...);
	}


}// namespace Platform

#endif // ifndef PLATFORM_REFOBJECT_H