#pragma once
#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#define COMPONENT_NUM (256)

namespace Engine
{
	namespace Internal
	{
		namespace detail
		{
			/**
			* @class    IComponentData
			* @brief    ComponentDataの基底クラス
			*/
			class IComponentData
			{
			public:
				IComponentData() = default;
				virtual ~IComponentData() = default;

			};// class IComponentData

			/**
			* @class    IComponentSystem
			* @brief    ComponentSystemの基底クラス
			*/
			class IComponentSystem
			{
			public:
				IComponentSystem() = default;
				virtual ~IComponentSystem() = default;

			};// class IComponentSystem

		}// namesapce Engine::Internal::detail
	}// namesapce Engine::Internal
}// namesapce Engine

namespace Engine
{
	namespace Internal
	{
		/**
		* @class    ComponentData
		* @brief    ComponentSystemで使うデータ
		*/
		class ComponentData : public detail::IComponentData
		{
		public:
			ComponentData() = default;
			virtual ~ComponentData() = default;

		};//class ComponentData

		/**
		* @class    ComponentSystem
		* @brief    ComponentDataを使ってシステムの動作を変更していく
		*/
		template<typename Type>
		class ComponentSystem : public detail::IComponentSystem
		{
		public:
			using Allocator = Core::PoolAllocator;

			/**
			* @brief    コンストラクタ
			* @param(size_t)		PoolAllocatorの確保サイズ
			* @param(const void*)	PoolAllocatorの先頭アドレス
			* @return   None
			*/
			ComponentSystem(size_t size,const void* address) :
				m_ObjectPool(size, address, sizeof(Type), alignof(Type))
			{

			}

			virtual ~ComponentSystem()
			{
				m_ObjectPool.Clear();
			}

			// Component 生成
			virtual Type* CreateComponent();
			// Component 処理
			virtual void Process(Type* data) = 0;
			// Component 破棄
			virtual void ReleaseComponent(Type* data);

		protected:
			/**
			*	ComponentDataを格納する
			*/
			Allocator m_ObjectPool;

		};// class ComponentSystem

		template<typename Type>
		inline Type* ComponentSystem<Type>::CreateComponent()
		{
			void* ptr = m_ObjectPool.Allocate(sizeof(Type), alignof(Type));
			if (ptr == nullptr)
			{
				LOG_ERROR("PoolAllocator is not enoght Memory Capacity of ComponentSystem");
				return nullptr;
			}
			return new(ptr) Type();
		}

		template<typename Type>
		inline void ComponentSystem<Type>::ReleaseComponent(Type* data)
		{
			m_ObjectPool.Free(data);
		}

	}// namesapce Engine::Internal
}// namesapce Engine

#endif // ifndef ENGINE_COMPONET_H