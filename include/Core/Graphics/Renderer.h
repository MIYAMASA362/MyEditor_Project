#pragma once
#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

/**
* @file     Renderer.h
* @author   unkown
* @brief    
* 
*	IRendererを利用したエンジンがサポートできるラッパークラス
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
		*	Thirdpartyから得られるRendererの内容をラップする
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