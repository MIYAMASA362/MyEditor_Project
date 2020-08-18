#include"Platform/Common.h"

#include"Platform/Base/ISystem.h"
#include"Platform/Base/IWindow.h"

#include"Platform/Windows/Window.h"

namespace Platform
{
	namespace Windows
	{

		Window::Window(detail::ISystem* main)
			:
			IWindow(main)
		{

		}

		Window::~Window()
		{

		}

		int Window::messageLoop()
		{
			MSG msg;

			m_System->Initialize();

			do
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					m_System->Update();
				}

			} while (msg.message != WM_QUIT);

			m_System->Finalize();

			return msg.wParam;
		}

	}//namespace Windows
}//namespace Platform