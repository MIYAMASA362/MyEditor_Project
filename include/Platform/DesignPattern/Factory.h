#pragma once
#ifndef PLATFORM_FACTORY_H
#define PLATFORM_FACTORY_H

#include<type_traits>

namespace detail
{
	/**
	* @class    IProduct
	* @brief	
	*/
	template<typename Type>
	class IProduct 
	{
	private:

	protected:
		IProduct() = default;
		virtual ~IProduct() = default;

	};//class IProduct


	/**
	* @class    IFactory
	* @brief    
	*/
	template<typename Type>
	class IFactory 
	{
		//static_assert(std::is_base_of<IProduct<Type>,Type>::value,"Type must inherit form IProduct");
	public:
		using Value_Type = Type;

	private:

	protected:
		IFactory() = default;

	public:
		virtual ~IFactory() = default;

		virtual Type* Create();
		virtual void Destroy(Type* instance);


	};//class IFactory


	//template<typename Type>
	//template<typename ...Args>
	//inline Type * IFactory<Type>::Create(Args ...args)
	//{
	//	/*static_assert(
	//		std::is_constructible<Type, Args...>::value,
	//		"This Argument type does not match the Type`s constructor");*/

	//	//åpè≥êÊÇ≈ê∂ê¨ï®ÇïœçXÇ∑ÇÈå`Ç…Ç∑ÇÈ
	//	return (Type*)internal_Create(std::forward<Args>(args)...);
	//}

	template<typename Type>
	inline Type* IFactory<Type>::Create()
	{
		return new Type();
	}

	template<typename Type>
	inline void IFactory<Type>::Destroy(Type * instance)
	{
		if(instance != nullptr)
			delete instance;
	}

}//namespace detail

#endif //ifndef PLATFORM_FACTORY_H