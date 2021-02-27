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
			class ENGINE_API IShader : public IResource
			{
			protected:
				IShader() = default;

			public:
				virtual ~IShader() = default;
				virtual void SetShaderResource() = 0;

			};// class IShader

		}// namespace Platform::Graphics::detail
	}// namespace Platform::Graphics
}// namespace Platform

#endif// ifndef PLATFORM_ISHADER_H