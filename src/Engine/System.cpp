#include "Config.h"

#include <vector>
#include <map>

// Platform Layer
#include "Platform/Base/Assert.h"
#include "Platform/Base/Result.h"

// Core Layer
#include "Core/System/Window.h"

// Engine Layer
#include "Engine/Base/System.h"

namespace Engine
{
	EngineDevice::EngineDevice(
		IN HINSTANCE hInstance,
		IN LPSTR lpClassName,
		IN LPSTR lpCaption,
		IN int x,
		IN int y,
		IN long width,
		IN long height,
		IN DWORD style
	):
		m_window(
			hInstance,
			lpClassName,
			lpCaption,
			x, y, 
			width, 
			height, 
			style
		)
	{
		
	}

	EngineDevice::~EngineDevice()
	{

	}

	int EngineDevice::ProcessLoop()
	{
		MSG msg;

		while (true)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//
				//	以下処理を並列処理
				//

				// ゲームオブジェクトの更新

				// 描画

			}
			if (msg.message == WM_QUIT) break;
		}
		return (int)msg.wParam;
	}

	void EngineDevice::Release()
	{

	}

}//namespace Engine