#pragma once
#ifndef PLATFORM_ISHADER_H
#define PLATFORM_ISHADER_H

namespace Platform
{
	namespace Graphics
	{
		enum class VERTEX_INPUT_LAYOUT
		{
			VSIL_POSITION,
			VSIL_NORMAL,
			VSIL_COLOR,
			VSIL_TEXCOORD
		};

		namespace detail
		{
			/**
			* @class    Shader Interface
			* @brief    シェーダインターフェイス
			* 
			* 
			*/
			class IShader : public IResource
			{
			protected:
				IShader() ENGINE_DEFAULT;
				virtual ~IShader() ENGINE_DEFAULT;

			public:
				virtual void SetShaderResource() ENGINE_PURE;

			};// class IShader

		}// namespace Platform::Graphics::detail


		/**
		* @class    class
		* @brief    Enum Description
		*/
		class IVertexShader : public detail::IShader
		{
		protected:
			IVertexShader() ENGINE_DEFAULT;
			virtual ~IVertexShader() ENGINE_DEFAULT;

		};// class IVertexShader

		/**
		* @class    class
		* @brief    Enum Description
		*/
		class IPixelShader : public detail::IShader
		{
		protected:
			IPixelShader() ENGINE_DEFAULT;
			virtual ~IPixelShader() ENGINE_DEFAULT;

		};// class IPixelShader

	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef PLATFORM_ISHADER_H