#define ENGINE_DIRECTX11
#define ENGINE_WINSOCK

#include<vector>
#include<map>

#include"Platform.h"
#include"Core.h"
#include"Engine.h"

#include "Core/Thread/Thread.h"
#include "Core/Time/Time.h"

#include "Core/Network/Network.h"

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

	// Module
	Core::Graphics::GraphicsModule graphicsModule("DirectX11.dll");
	graphicsModule.CreateRenderer(window.GetHWnd(),&mainSystem.m_Renderer);

	Core::Network::NetworkModule networkModule("Winsock.dll");
	::Platform::Network::detail::INetwork* network;
	networkModule.CreateNetwork(&network);
	network->Startup();
	network->Cleanup();
	networkModule.ReleaseNetwork(&network);

	mainSystem.mainLoop();

	graphicsModule.ReleaseRenderer(&mainSystem.m_Renderer);

	Core::Thread th1([]() 
	{
		LOG_DEBUG("Thread 1 Processing");
		std::this_thread::sleep_for(Core::Time::NanoSeconds(1));
	});
	th1.run();
	LOG_DEBUG("Thread End");

	return 0;
}