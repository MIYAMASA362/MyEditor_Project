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
			* @brief    ComponentData�̊��N���X
			*/
			class IComponentData
			{
			public:
				IComponentData() = default;
				virtual ~IComponentData() = default;

			};// class IComponentData

			/**
			* @class    IComponentSystem
			* @brief    ComponentSystem�̊��N���X
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
		* @brief    ComponentSystem�Ŏg���f�[�^
		*/
		class ComponentData : public detail::IComponentData
		{
		public:
			ComponentData() = default;
			virtual ~ComponentData() = default;

		};//class ComponentData

		/**
		* @class    ComponentSystem
		* @brief    ComponentData���g���ăV�X�e���̓����ύX���Ă���
		*/
		template<typename Type>
		class ComponentSystem : public detail::IComponentSystem
		{
		public:
			using Allocator = Core::PoolAllocator;

			/**
			* @brief    �R���X�g���N�^
			* @param(size_t)		PoolAllocator�̊m�ۃT�C�Y
			* @param(const void*)	PoolAllocator�̐擪�A�h���X
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

			// Component ����
			virtual Type* CreateComponent();
			// Component ����
			virtual void Process(Type* data) = 0;
			// Component �j��
			virtual void ReleaseComponent(Type* data);

		protected:
			/**
			*	ComponentData���i�[����
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