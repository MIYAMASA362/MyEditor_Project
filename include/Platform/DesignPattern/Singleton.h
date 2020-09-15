#pragma once
#ifndef PLATFORM_SINGLETON_H
#define PLATFORM_SINGLETON_H

namespace detail
{
	/**
	* @class    Singleton
	* @brief    
	*/
	template<typename T>
	class Singleton
	{
	protected:
		static T* g_pInstance;

		Singleton() = default;
		virtual ~Singleton() = default;

	public:
		static T* GetInstance();
		static void Create();
		static void Destroy();

	};//class Singleton

	template<typename T>T* Singleton<T>::g_pInstance = nullptr;

	template<typename T>
	inline T * Singleton<T>::GetInstance()
	{
		return g_pInstance;
	}

	template<typename T>
	inline void Singleton<T>::Create()
	{
		g_pInstance = new T();
	}

	template<typename T>
	inline void Singleton<T>::Destroy()
	{
		delete g_pInstance;
		g_pInstance = nullptr;
	}

}//namespace detail

#endif //ifndef PLATFORM_SINGLETON_H