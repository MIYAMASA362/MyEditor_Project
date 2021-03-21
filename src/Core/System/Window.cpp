#include"Config.h"

#ifdef ENGINE_WIN
#include<Windows.h>
#else // ifdef ENGINE_WIN

#endif

#include"Core/System/Window.h"

namespace Core
{

#ifdef ENGINE_WIN

	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (uMsg == WM_CREATE)
		{
			window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;

			if (window != nullptr) window->SetProcParam(hWnd);
		}

		if (window != nullptr) return window->localWndProc(hWnd, uMsg, wParam, lParam);

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	Window::Window(HINSTANCE hInstance, LPSTR lpClassName, LPSTR lpCaption, int x, int y, long width, long height, DWORD style)
	{
		//WndClassÝ’è
		WNDCLASSEX WndClass = {
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			WndProc,
			0,
			0,
			hInstance,
			NULL,
			LoadCursor(NULL,IDC_ARROW),
			(HBRUSH)(COLOR_WINDOW + 1),
			NULL,
			lpClassName,
			NULL
		};

		if (!RegisterClassEx(&WndClass)) {
			MessageBox(NULL, "WndClass‚ÌÝ’è‚ÉŽ¸”s‚µ‚Ü‚µ‚½B", "Ž¸”s", MB_OK);
			return;
		}

		//hWndÝ’è
		this->m_hWnd = CreateWindowEx(
			0,
			lpClassName,
			lpCaption,
			style,
			x, y,
			width + GetSystemMetrics(SM_CXDLGFRAME) * 2,
			height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL,
			NULL,
			hInstance,
			this
		);

		if (!this->m_hWnd) {
			MessageBox(NULL, "hWnd‚ÌÝ’è‚ÉŽ¸”s‚µ‚Ü‚µ‚½B", "Ž¸”s", MB_OK);
			return;
		}

		//•\Ž¦
		ShowWindow(this->m_hWnd, SW_SHOW);
		UpdateWindow(this->m_hWnd);
	}

	Window::~Window()
	{

	}


	LRESULT Window::localWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			default:
				break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return 0;
	}

	void Window::SetProcParam(HWND hWnd)
	{
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
		this->m_hWnd = hWnd;
	}

#endif // ifdef ENGINE_WIN

}// namespace Core