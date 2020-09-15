#include "stdafx.h"

namespace Core
{
	DX11GraphicsFactory::DX11GraphicsFactory()
	{
		::Platform::Graphics::DX11Graphics::Create();
	}

	DX11GraphicsFactory::~DX11GraphicsFactory()
	{
		::Platform::Graphics::DX11Graphics::Destroy();
	}

	void DX11GraphicsFactory::create(HWND hWnd,DX11GraphicsFactory::Value_Type** output)
	{
		 (*output) = new Platform::Graphics::DX11Renderer(hWnd);
	}

	void DX11GraphicsFactory::release(DX11GraphicsFactory::Value_Type** instance)
	{
		delete *instance;
		*instance = nullptr;
	}

	extern "C" ENGINE_API IGraphicsFactory* base_GetGraphicsFactory()
	{
		return new DX11GraphicsFactory();
	}

	extern "C" ENGINE_API void base_ReleaseGraphicsFactory(IGraphicsFactory** instance)
	{
		delete dynamic_cast<DX11GraphicsFactory*>(*instance);
	}

}//namespace Core