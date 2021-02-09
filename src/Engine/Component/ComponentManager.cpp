#include"Config.h"

#include<vector>
#include<map>
#include<typeinfo>

#include"Platform/Base/Logger.h"
#include"Platform/Base/Assert.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/PoolAllocator.h"
#include"Core/Allocator/StackAllocator.h"

#include"Engine/Component/Component.h"
#include"Engine/Component/ComponentManager.h"

namespace Engine
{
	namespace Internal
	{
		static void* g_pGlobalMemory = nullptr;

		Core::StackAllocator* ComponentManager::m_StackAllocator;

		ComponentManager::ComponentManager()
		{
			g_pGlobalMemory = malloc(MEMORY_CAPACITY);
			m_StackAllocator = new Core::StackAllocator(MEMORY_CAPACITY,g_pGlobalMemory);
		}

		ComponentManager::~ComponentManager()
		{
			m_StackAllocator->Clear();
			delete m_StackAllocator;
			m_StackAllocator = nullptr;

			free(g_pGlobalMemory);
			g_pGlobalMemory = nullptr;
		}

		Core::StackAllocator* ComponentManager::GetAllocator()
		{
			return this->m_StackAllocator;
		}

	}
}