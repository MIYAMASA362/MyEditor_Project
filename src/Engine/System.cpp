#include "Config.h"

#include<vector>
#include<map>

// Platform Layer
#include "Platform/Base/ISystem.h"
#include "Platform/Base/IRenderer.h"
#include "Platform/Module/Module.h"

// Core Layer
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
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				this->ProcessModule(Core::System::ModuleType::Update);

				if(m_Renderer) m_Renderer->clear();

				if(m_Renderer) m_Renderer->begin();

				this->ProcessModule(Core::System::ModuleType::Render);

				if(m_Renderer) m_Renderer->end();
			}

		} while (msg.message != WM_QUIT);

		this->ProcessModule(Core::System::ModuleType::Finalize);

		return (int)msg.wParam;
	}

}//namespace Engine