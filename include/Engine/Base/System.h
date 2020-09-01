#pragma once
#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

namespace Engine
{
	class System final : public Platform::detail::ISystem
	{
	private:
		
	public:
		Platform::detail::IRenderer* m_Renderer;

	public:

		System();
		virtual ~System();

		virtual int mainLoop() override;

	};//class System

}//namespace Engine

#endif //ifndef ENGINE_H