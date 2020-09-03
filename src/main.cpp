#define ENGINE_DIRECTX11

#include <stdlib.h>  
#include <crtdbg.h> 

#include<string>

#include"Platform.h"
#include"Core.h"
#include"Engine.h"

#include"Editor/Console/Console.h"



int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	Editor::detail::Console console;
	console.create();

	TCHAR curDir[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1,curDir);

	Core::Path path(curDir);
	auto file = path.getFile();

	Platform::Windows::Window window;
	window.Create(
		hInstance,
		(LPSTR)"MainWindow",
		(LPSTR)"MainWindow",
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,576,
		WS_OVERLAPPEDWINDOW
	);

	Platform::Graphics::DX11Graphics::Create();

	Engine::System mainSystem;
	mainSystem.m_Renderer = new Platform::Graphics::DX11Renderer(window.GetHWnd());
	mainSystem.mainLoop();

	Platform::Graphics::DX11Graphics::Destroy();
	
	console.close();

	return 0;
}