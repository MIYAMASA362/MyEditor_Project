#pragma once
#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

namespace Engine
{
	namespace Internal
	{
		namespace detail
		{
			class IComponentData
			{
			
			};

			class IComponentSystem
			{
			
			};

		}// namesapce Engine::Internal::detail
	}// namesapce Engine::Internal
}// namesapce Engine

namespace Engine
{
	namespace Internal
	{
		class ComponentData : public detail::IComponentData
		{
		
		};

		class ComponentSystem : public detail::IComponentSystem
		{
		
		};

	}// namesapce Engine::Internal
}// namesapce Engine

#endif // ifndef ENGINE_COMPONET_H