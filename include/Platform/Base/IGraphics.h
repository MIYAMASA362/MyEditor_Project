#pragma once
#ifndef PLATFORM_GRAPHICS_H
#define PLATFORM_GRAPHICS_H

namespace Platform
{
	namespace Graphics
	{
		enum class PRIMITIVE_TYPES
		{
			POINTLIST = 0,
			LINELIST,
			LINESTRIP,
			TRIANGLELIST,
			TRIANGLESTRIP
		};

		namespace detail
		{
			/**
			* @class    IGraphics
			* @brief    Graphics Interface
			*
			*	ï`âÊã§í ê›íË
			*
			*/
			class IGraphics
			{
			public:
				using Value_Type = ::Platform::Graphics::detail::IRenderer;

				IGraphics() ENGINE_DEFAULT;
				virtual ~IGraphics() ENGINE_DEFAULT;


				// Renderer
				virtual void CreateRenderer(
					IN::Platform::detail::IWindow* iWindow,
					OUT IRenderer** output
				) ENGINE_PURE;

				virtual void ReleaseRenderer(
					IN IRenderer**
				) ENGINE_PURE;


				// VertexShader
				virtual void CreateVertexShader(
					IN const void* buffer,
					IN const unsigned long size,
					IN VERTEX_INPUT_LAYOUT* inputlayout,
					IN const unsigned int layoutSize,
					OUT IVertexShader**
				) ENGINE_PURE;

				virtual void ReleaseVertexShader(
					IN IVertexShader**
				) ENGINE_PURE;


				// PixelShader
				virtual void CreatePixelShader(
					IN const void* buffer,
					IN const unsigned long size,
					OUT IPixelShader**
				) ENGINE_PURE;

				virtual void ReleasePixelShader(
					IN IPixelShader**
				) ENGINE_PURE;


				// ConstantBuffer
				virtual void CreateConstantBuffer(
					IN unsigned int byteWidth,
					IN unsigned int byteStride,
					OUT IConstantBuffer**
				) ENGINE_PURE;

				virtual void ReleaseConstantBuffer(
					IN IConstantBuffer**
				) ENGINE_PURE;


				// IndexBuffer
				virtual void CreateIndexBuffer(
					IN const void* index,
					IN unsigned int size,
					IN unsigned int indexNum,
					OUT IIndexBuffer**
				) ENGINE_PURE;

				virtual void ReleaseIndexBuffer(
					IN IIndexBuffer**
				) ENGINE_PURE;


				// VertexBuffer
				virtual void CreateVertexBuffer(
					IN const void* vertex,
					IN unsigned int size,
					IN unsigned int vertexNum,
					OUT IVertexBuffer**
				) ENGINE_PURE;

				virtual void ReleaseVertexBuffer(
					IN IVertexBuffer**
				) ENGINE_PURE;


				// Topology
				virtual void SetPrimitiveTopology(
					IN PRIMITIVE_TYPES type
				) ENGINE_PURE;


				// DrawIndexed
				virtual void DrawIndexed(
					IN unsigned int IndexCount,
					IN unsigned int StartIndexLocation,
					IN unsigned int BaseVertexLocation
				) ENGINE_PURE;


			};// class IGraphics

		}// namespace Platform::Graphics::detail
	}// namespace Platform::Graphics
}// namespace Platform

#endif // ifndef PLATFORM_GRAPHICS_H