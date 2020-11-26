#pragma once
#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

namespace Engine
{
	/**
	* @class    System
	* @brief	�A�v���P�[�V�����̊�V�X�e��
	*/
	class System final : public Core::System::ISystem
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