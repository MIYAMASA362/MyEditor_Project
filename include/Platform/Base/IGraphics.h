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
				virtual void CreateRenderer(::Platform::detail::IWindow* iWindow, IRenderer** output) = 0;
				virtual void ReleaseRenderer(IRenderer** instance) = 0;

				// VertexShader
				virtual void CreateVertexShader(const void* buffer, const unsigned long size, VERTEX_INPUT_LAYOUT* inputlayout, const unsigned int layoutSize, detail::IShader** output) = 0;
				virtual void ReleaseVertexShader(detail::IShader** instance) = 0;

				// PiexlShader
				virtual void CreatePixelShader(const void* buffer, const unsigned long size, detail::IShader** output) = 0;
				virtual void ReleasePixelShader(detail::IShader** instance) = 0;

				// ConstantBuffer
				virtual void CreateConstantBuffer(unsigned int byteWidth, unsigned int byteStride, detail::IConstantBuffer** output) = 0;

				// IndexBuffer
				virtual void CreateIndexBuffer(const void* index, unsigned int size, unsigned int indexNum, detail::IIndexBuffer** output) = 0;

				// VertexBuffer
				virtual void CreateVertexBuffer(const void* vertex, unsigned int size, unsigned int vertexNum, detail::IVertexBuffer** output) = 0;

			};// class IGraphics

		}// namespace Platform::Graphics::detail
	}// namespace Platform::Graphics
}// namespace Platform

#endif // ifndef PLATFORM_GRAPHICS_H