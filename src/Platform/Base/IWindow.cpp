#include "Platform/Common.h"

#include "Platform/Base/ISystem.h"
#include "Platform/Base/IWindow.h"

namespace Platform
{
	namespace detail
	{
		IWindow::IWindow(ISystem * main)
			:
			m_System(main)
		{

		}

		IWindow::~IWindow()
		{
			
		}

	}//namespace Platform::detail
}//namespace Platform
