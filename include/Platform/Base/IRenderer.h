#pragma once
#ifndef PLATFORM_IRENDERER_H
#define PLATFORM_IRENDERER_H

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{
			/**
			* @class    IRenderer
			* @brief    Renderer Intarface
			* 
			*	�w��̈���ł̕`�揈��
			* 
			* 
			*/
			class ENGINE_API IRenderer
			{
			protected:

			public:
				IRenderer() {};
				virtual ~IRenderer() {};

				virtual void clear() = 0;
				virtual void begin() = 0;
				virtual void end() = 0;

			};//class IRenderer

		}//namespace Platform::Graphics::detail
	}// namespace Platform::Graphics
}//namespace Platform

#endif //ifndef PLATFORM_IRENDERER_H