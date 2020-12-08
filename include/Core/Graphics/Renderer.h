#pragma once
#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

namespace Core
{
	namespace Graphics
	{
		/**
		* @class    Renderer
		* @brief    
		*	Thirdparty‚©‚ç“¾‚ç‚ê‚éRenderer‚Ì“à—e‚ðƒ‰ƒbƒv‚·‚é
		* 
		*/
		class Renderer : public ::Platform::Graphics::detail::IRenderer
		{
		public:
			Renderer();
			virtual ~Renderer();

			virtual void clear() override;
			virtual void begin() override;
			virtual void end() override;

		private:
			::Platform::Graphics::detail::IRenderer* m_Renderer;

		};// namespace Renderer

	}// namespace Core::Graphics
}// namespace Core

#endif // ifndef CORE_RENDERER_H