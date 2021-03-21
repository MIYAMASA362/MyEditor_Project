#include "Config.h"

#include<vector>
#include<map>

// Platform Layer
#include"Platform/Base/Assert.h"

#include "Platform/Base/ISystem.h"
#include "Platform/Base/IRenderer.h"
#include "Platform/Base/IModule.h"
#include "Platform/Base/Result.h"

// Core Layer
#include"Core/System/Window.h"
#include "Core/System/ISystemModule.h"
#include "Core/System/System.h"

// Engine Layer
#include "Engine/Base/System.h"

namespace Engine
{
	System::System()
		:
		m_Renderer(nullptr)
	{

	}

	System::~System()
	{
		if (m_Renderer) delete m_Renderer;
	}

	int System::mainLoop()
	{
		MSG msg;

		this->ProcessModule(Core::System::ModuleType::Initialize);

		do
		{
			// メッセージポンプ
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// ゲームループ

				// レンダリングループ

				this->ProcessModule(Core::System::ModuleType::Update);

				if (m_Renderer) m_Renderer->clear();

				if (m_Renderer) m_Renderer->begin();

				this->ProcessModule(Core::System::ModuleType::Render);

				if (m_Renderer) m_Renderer->end();
			}

		} while (msg.message != WM_QUIT);

		this->ProcessModule(Core::System::ModuleType::Finalize);

		return (int)msg.wParam;
	}

#ifdef ENGINE_WIN
	Result CreateEngine(
		IN HINSTANCE hInstance,
		IN LPSTR lpClassName,
		IN LPSTR lpCaption,
		IN int x,
		IN int y,
		IN long width,
		IN long height,
		IN DWORD style,
		OUT EngineDevice** output)
	{
		(*output) = new EngineDevice();

		// システムのメインウィンドウ
		Core::Window main(hInstance,lpClassName,lpCaption,x,y,width,height,style);

		

		return Result(true);
	}

#else

#endif

	int EngineDevice::ProcessLoop()
	{
#ifdef ENGINE_WIN
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
				//以下処理を並列処理

				// ゲームオブジェクトの更新

				// 描画
			}
			if (msg.message == WM_QUIT) break;
		}
		return (int)msg.wParam;
#endif
	}

}//namespace Engine