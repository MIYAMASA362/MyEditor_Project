#define ENGINE_DIRECTX11

#include <stdlib.h>  
#include <crtdbg.h> 

#include<string>

#include"Platform.h"
#include"Core.h"
#include"Engine.h"

#include"Editor/Console/Console.h"

#include"Core/IO/DllLoader.h"

#include"Core/Module/GraphicsFactory.h"

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	TCHAR curDir[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1,curDir);

	//Core::FileStream* stream;
	//Core::FileStream::create("StreamTest.txt",Core::FileMode::ReadWrite,&stream);

	//stream->writeFormat("[Initialize]\n[Update]\n[Renderer]\n[Finalize]");
	//stream->seek(10,Core::StreamSeek::Begin);

	//stream->seekFind("[Update]");
	//std::string str(100, '\0');
	//stream->read(str);

	//delete stream;

	//Core::DllLoader GraphicLoder;
	//GraphicLoder.getProcess(TO_STRING(Platform::Graphics::DX11Graphics));
	//

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

	Engine::System mainSystem;

	//Module
	Core::GraphicsModule graphicsModule("DirectX11.dll");

	graphicsModule.CreateRenderer(window.GetHWnd(),&mainSystem.m_Renderer);

	mainSystem.mainLoop();

	graphicsModule.ReleaseRenderer(&mainSystem.m_Renderer);

	return 0;
}