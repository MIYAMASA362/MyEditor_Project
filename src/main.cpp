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

	// Platform
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

	// MainSystem
	Engine::System mainSystem;

	// Graphics Module
	Core::Graphics::GraphicsModule graphicsModule("DirectX11.dll");
	graphicsModule.CreateRenderer(window.GetHWnd(),&mainSystem.m_Renderer);

	// Network Module
	Core::Network::NetworkModule networkModule("Winsock.dll");
	::Platform::Network::detail::INetwork* network;
	networkModule.CreateNetwork(&network);

	network->Startup();

	// Thread
	Core::Thread server([network](){
		::Platform::Network::detail::ISocket* iSocket = nullptr;

		::Platform::Network::SocketInfo info;
		info.m_address = NULL;
		info.m_port = "27015";
		info.m_flags = ::Platform::Network::Flags::PASSIVE;
		
		if (network->Create(&iSocket, info) == Platform::Network::FAILED){
			network->Release(&iSocket);
			return;
		}
		if (network->Bind(iSocket) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		if (network->Listen(iSocket) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		::Platform::Network::detail::ISocket* iClient = nullptr;

		if(network->Accept(iSocket,&iClient) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		network->Release(&iSocket);

		int iResult = 0;
		char buf[256];
		do
		{
			LOG_DEBUG("Server Idle");
			iResult = network->Recv(iClient,buf,256);
			if(iResult > 0)
			{
				int send = network->Send(iClient,buf,iResult);
				if(send == Platform::Network::FAILED) {
					network->Release(&iClient);
					return;
				}
				buf[send] = '\0';
				LOG_DEBUG("Recived Message : %s",buf);
				break;
			}
			else if(iResult == 0)
			{
				
			}
			else
			{
				break;
			}
		} while (iResult>0);

		network->Close(iClient,::Platform::Network::CloseType::BOTH);
		network->Release(&iClient);

		LOG_DEBUG("Server Thread End");
	});

	Core::Thread client([network](){
		std::this_thread::sleep_for(Core::Time::Seconds(3));

		::Platform::Network::detail::ISocket* iSocket = nullptr;

		::Platform::Network::SocketInfo info;
		info.m_address = "localhost";
		info.m_port = "27015";

		if (network->Create(&iSocket, info) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		if (network->Connect(iSocket) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		char buf[256];
		const char* sendbuf = "this is a test";
		int iResult = 0;
		iResult = network->Send(iSocket,sendbuf,(int)strlen(sendbuf));
		if(iResult == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		do
		{
			LOG_DEBUG("Client Idle");
			iResult = network->Recv(iSocket,buf,256);
		} while (iResult > 0);

		network->Close(iSocket,::Platform::Network::CloseType::SEND);
		network->Release(&iSocket);

		LOG_DEBUG("Client Thread End");
	});

	// MainLoop
	mainSystem.mainLoop();

	client.run();
	server.run();

	network->Cleanup();

	// Release Module
	networkModule.ReleaseNetwork(&network);
	graphicsModule.ReleaseRenderer(&mainSystem.m_Renderer);

	return 0;
}