#include "stdafx.h"

#include "Platform/Base/ISystem.h"
#include "Platform/Base/IRenderer.h"
#include "Engine/Base/System.h"

namespace Engine
{
	System::System()
	{
		
	}

	System::~System()
	{
		if (m_Renderer)
			delete m_Renderer;
	}

	int System::mainLoop()
	{
		MSG msg;

		do
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				m_Renderer->clear();

				m_Renderer->begin();

				m_Renderer->end();
			}

		} while (msg.message != WM_QUIT);

		return (int)msg.wParam;
	}

}//namespace Engine