#include "stdafx.h"
//
//namespace Core
//{
//	namespace detail
//	{
//		EXTERN_C ENGINE_API ::Platform::Graphics::detail::IGraphics* base_GetGraphicsFactory()
//		{
//			return new ThirdParty::Core::DX11GraphicsFactory();
//		}
//
//		EXTERN_C ENGINE_API void base_ReleaseGraphicsFactory(::Platform::Graphics::detail::IGraphics** instance)
//		{
//			delete dynamic_cast<ThirdParty::Core::DX11GraphicsFactory*>(*instance);
//		}
//	}// namesapce Core::detail
//}// namespace Core
//
//namespace ThirdParty
//{
//	namespace Core
//	{
//		DX11GraphicsFactory::DX11GraphicsFactory()
//		{
//			Platform::Graphics::DX11Graphics::Create();
//		}
//
//		DX11GraphicsFactory::~DX11GraphicsFactory()
//		{
//			Platform::Graphics::DX11Graphics::Destroy();
//		}
//
//		void DX11GraphicsFactory::CreateRenderer(HWND hWnd, DX11GraphicsFactory::Value_Type** output)
//		{
//			(*output) = new ::Platform::Graphics::DX11Renderer(hWnd);
//		}
//
//		void DX11GraphicsFactory::ReleaseRenderer(DX11GraphicsFactory::Value_Type** instance)
//		{
//			delete *instance;
//			*instance = nullptr;
//		}
//	}// namespace ThirdParty::Core
//}// namespace ThirdParty