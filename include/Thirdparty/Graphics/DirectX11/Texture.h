#pragma once
#ifndef THIRDPARTY_DIRECTX11_TEXTURE_H
#define THIRDPARTY_DIRECTX11_TEXTURE_H

namespace Platform
{
	namespace Graphics
	{
		namespace Textures
		{
			/**
			* @class    Texture class
			* @brief    テクスチャ
			*/
			class ENGINE_API Texture
			{
			protected:
				ID3D11Texture2D* m_Source;
				ID3D11ShaderResourceView* m_SRV;

			public:
				Texture();
				virtual ~Texture();

				// テクスチャ読み込み
				void LoadTexture(const void* pixels,unsigned int width,unsigned int height,unsigned int bpp);
				// リソース設定
				void SetResource(unsigned int slot = 0,unsigned int view = 1);

			};//class Texture

		}// namespace Platform::Graphics::Textures
	}//namespace Platform::Graphics
}//namespace Platform

#endif // ifndef THIREDPARTY_DIRECTX11_TEXTURE_H