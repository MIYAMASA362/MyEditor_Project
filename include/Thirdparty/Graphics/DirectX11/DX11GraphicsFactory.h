#pragma once
#ifndef CORE_DX11GRAPHICSFACTORY_H
#define CORE_DX11GRAPHICSFACTORY_H

namespace Core
{
	class ENGINE_API DX11GraphicsFactory : public IGraphicsFactory
	{
	private:

	public:
		DX11GraphicsFactory();
		virtual ~DX11GraphicsFactory();

		virtual void create(HWND hWnd,Value_Type** output) override;
		virtual void release(DX11GraphicsFactory::Value_Type** instance) override;

	};//DX11GraphicsFactory

}//namespace Core

#endif //CORE_DX11GRAPHICSFACTORY_H