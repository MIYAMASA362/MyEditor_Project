#pragma once
#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

namespace Engine
{
	namespace Renderer
	{
		class RendererComponentData : public Internal::ComponentData
		{
		public:


		public:
			RendererComponentData();
			virtual ~RendererComponentData();

		};// classs RendererComponentData

		class RendererComponentSystem : public Internal::ComponentSystem<RendererComponentData>
		{
		public:
			RendererComponentSystem(size_t size, const void* address);
			virtual ~RendererComponentSystem();

			virtual void Process(RendererComponentData* data) override;

		};// class RendererComponentSystem
		

	}// namespace Engine::Renderer
}// namesapce Engine

#endif // ifndef ENGINE_RENDERER_H