#pragma once
#ifndef THIRDPARTY_DIRECTX11_FACTORY_H
#define THIRDPARTY_DIRECTX11_FACTORY_H

namespace ThirdParty
{
	namespace Core
	{
		class ENGINE_API DX11GraphicsFactory : public ::Core::Graphics::IGraphicsFactory
		{
		private:

		public:
			DX11GraphicsFactory();
			virtual ~DX11GraphicsFactory();

			virtual void create(HWND hWnd, Value_Type** output) override;
			virtual void release(DX11GraphicsFactory::Value_Type** instance) override;

		};// class DX11GraphicsFactory
	}// namespace ThirdParty::Core
}// namespace ThirdParty

#endif //THIRDPARTY_DIRECTX11_FACTORY_H