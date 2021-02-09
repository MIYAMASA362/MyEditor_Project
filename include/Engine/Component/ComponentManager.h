#pragma once
#ifndef ENGINE_COMPONENTMANAGER_H
#define ENGINE_COMPONENTMANAGER_H

/**
* @file     ComponentManager.h
* @author   unkown
* @brief    
* 
*	* ComponentManager
*	|	StackAllocator : Managed MemorySize	(128MB)	|
*	| ComponentSystem | .....						|
* 
*	* ComponentSystem
*	|	PoolAllocator : Managerd MemorySize	(ComponentData Size * 256)Byte	|
*	| ComponentData | .....													|
* 
*/

#define COMPONENT_OBJECT_NUM 256 // 256個
#define COMPONENT_MANAGER_CAPACITY 134217728 // 128MB

namespace Engine
{
	namespace Internal
	{
		/**
		* @class    ComponentManager
		* @brief    コンポーネントの管理者
		*/
		class ComponentManager
		{
			// StackAllocatorが確保するサイズ
			static constexpr size_t MEMORY_CAPACITY = COMPONENT_MANAGER_CAPACITY;

		public:
			ComponentManager();
			virtual ~ComponentManager();

			template<typename System,typename DataType>
			System* CreateSystem()
			{
				size_t size = sizeof(System) + (sizeof(DataType) * COMPONENT_OBJECT_NUM);
				void* ptr = m_StackAllocator->Allocate(size, alignof(DataType));
				if(ptr == nullptr)
				{
					LOG_ERROR("StackAllocator is not enoght Memory Capacity of ComponentManager");
					return nullptr;
				}

				union
				{
					void* asVoidPtr;
					uptr asUptr;
				};

				asVoidPtr = ptr;
				asUptr += sizeof(System);

				size -= sizeof(System);
				ptr = new(ptr) System(size, asVoidPtr);
				return (System*)ptr;
			};

			template<typename System,typename DataType>
			void ReleaseSystem(System** address)
			{
				m_StackAllocator->Free(*address);
				*address = nullptr;
			}
			
			Core::StackAllocator* GetAllocator();

		private:
			/**
			* ComponentManagerに登録されたComponentSystemをStackAllocatorから確保して返す
			* ・ComponentSystemは対象のComponentDataのObjectPool(size * 256)を保有している
			*/
			static Core::StackAllocator* m_StackAllocator;

		};// class ComponentManager

	}// namespace Engine::Internal
}// namespace Engine

#endif// ifndef ENGINE_COMPONENTMANAGER_H