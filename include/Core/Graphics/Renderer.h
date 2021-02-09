#pragma once
#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

/**
* @file     Renderer.h
* @author   unkown
* @brief    
* 
*	IRenderer�𗘗p�����G���W�����T�|�[�g�ł��郉�b�p�[�N���X
* 
* 
*/

namespace Core
{
	namespace Graphics
	{
		typedef ::Platform::Graphics::detail::IRenderer IRenderer;

		/**
		* @class    Renderer
		* @brief    
		*	Thirdparty���瓾����Renderer�̓��e�����b�v����
		* 
		*/
		class Renderer
		{
		public:
			Renderer();
			virtual ~Renderer();

		private:
			IRenderer* m_Renderer;


		};// namespace Renderer

	}// namespace Core::Graphics
}// namespace Core

#endif // ifndef CORE_RENDERER_H