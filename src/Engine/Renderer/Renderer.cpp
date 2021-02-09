#include"Config.h"

#include"Platform/Base/Logger.h"
#include"Platform/Base/Assert.h"

#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/PoolAllocator.h"

#include"Engine/Component/Component.h"

#include"Engine/Renderer/Renderer.h"

namespace Engine
{
	namespace Renderer
	{
		RendererComponentData::RendererComponentData()
		{

		}

		RendererComponentData::~RendererComponentData()
		{

		}

		RendererComponentSystem::RendererComponentSystem(size_t size, const void* address)
			:
			Internal::ComponentSystem<RendererComponentData>(size,address)
		{
			
		}

		RendererComponentSystem::~RendererComponentSystem()
		{

		}

		void RendererComponentSystem::Process(RendererComponentData* data)
		{

		}

	}// namespace Engine::Renderer
}// namespace Engine