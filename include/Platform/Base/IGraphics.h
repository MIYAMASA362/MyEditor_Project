#pragma once
#ifndef PLATFORM_GRAPHICS_H
#define PLATFORM_GRAPHICS_H

namespace Platform
{
	namespace Graphics
	{
		namespace detail
		{
			/**
			* @class    IGraphics
			* @brief    Graphics Interface
			*	
			*	ï`âÊã§í ê›íË
			* 
			*/
			class ENGINE_API IGraphics
			{
			public:
				using Value_Type = ::Platform::Graphics::detail::IRenderer;

				IGraphics() {};
				virtual ~IGraphics() {};

				// Renderer
				virtual void CreateRenderer(HWND hWnd,IRenderer** output) = 0;
				virtual void ReleaseRenderer(IRenderer** instance) = 0;
				
				//  
				virtual void CreateVertexShader(const char* fileNAme, detail::IVertexShader** output) =0;
				virtual void CreatePixelShader(const char* fileName, detail::IPixelShader** output) =0;

			};// class IGraphics

		}// namespace Platform::Graphics::detail

	}// namespace Platform::Graphics
}// namespace Platform

#endif // ifndef PLATFORM_GRAPHICS_H