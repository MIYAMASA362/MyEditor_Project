/****************************************************************************************
*
*	< 課題 >
*	1.並列プログラミング
*	
*	2.描画システム
* 
*	3.リソース制御
*		リソースマネージャ
*		シェーダ？
* 
*	< 指針 >
*	
* 
* 
****************************************************************************************/

#define ENGINE_DIRECTX11
#define ENGINE_WINSOCK

#include<vector>
#include<map>

#include"Platform.h"
#include"Core.h"
#include"Engine.h"

/**
*
*	WinMain
*
*
*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Result result(false);

	Core::Window window(
		hInstance,
		(LPSTR)"MainWindow",
		(LPSTR)"MainWindow",
		CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 576,
		WS_OVERLAPPEDWINDOW
	);

	// RendererModule
	Core::RendererModule rendererModule("DirectX11.dll");

	// RendererDevice
	Platform::IRendererDevice* device;
	result = rendererModule.CreateRendererDevice(&device);
	if (!result) return 0;

	// Renderer
	Platform::IRenderer* renderer;
	result = device->CreateRenderer(window.GetHWnd(),&renderer);
	if(!result)
	{
		device->Release();
		return 0;
	}

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
			renderer->Clear();
			renderer->Begin();

			renderer->End();
		}
		if (msg.message == WM_QUIT) break;
	}

	renderer->Release();

	device->Release();

	return (int)msg.wParam;
}

//
//	//###################################################################################
//	/**
//	*
//	*	FileStream
//	*
//	*
//	*/
//#if 0
//
//	Platform::IO::FileStream* stream;
//	Platform::IO::FileStream::create("StreamTest.txt", Platform::IO::FileMode::ReadWrite, &stream);
//
//	stream->writeFormat("[Initialize]\n[Update]\n[Renderer]\n[Finalize]");
//	stream->seek(10, Platform::IO::StreamSeek::Begin);
//
//	stream->seekFind("[Update]");
//	std::string str(100, '\0');
//	stream->read(str);
//
//	stream->close();
//	delete stream;
//
//	Platform::IO::DllLoader GraphicLoder;
//	GraphicLoder.getProcess(TO_STRING(Platform::Graphics::DX11Graphics));
//
//#endif
//
//	//###################################################################################
//	/**
//	*
//	*	OpenGLなどのシェーダに独自対応するためには、独自のシェーダ定義フォーマットファイルを作成する必要がある
//	*	独自のシェーダからHLSLを抽出して定義、内部コンパイルでcsoなどのリソースを吐き出す。
//	*	または内部で確保・隠ぺいしておく
//	*
//	*	HLSL コンパイル fxc.exe (SDK/utility/bin/x86)
//	*
//	*	独自のシェーダファイルをプリコンパイルさせる際に利用する
//	*	エフェクトファイルの隠ぺいなどに利用できる可能性もあるので要確認
//	*
//	*	Qiita : HLSLのオフラインコンパイル時に気を付けること
//	*	・https://qiita.com/shiro_naga/items/c1bac277df82fdd8bf52
//	*	・
//	*
//	*/
//#if 0
//	char path[MAX_PATH + 1];
//	strcpy_s(path, curDir);
//
//	// fxファイル
//	system("C:\\Users\\MIYAM\\Desktop\\MyEditor_Project\\external\\fxc.exe TestShader.hlsl /T fx_5_0 /Fo Test.cfx");
//
//#endif
//
//	// Engine
//	Engine::System* mainSystem = new Engine::System();
//
//	// Platform
//	Platform::detail::IWindow* iWindow;
//	//iWindow = new Platform::Windows::Window(
//	//	hInstance,
//	//	(LPSTR)"MainWindow",
//	//	(LPSTR)"MainWindow",
//	//	CW_USEDEFAULT, CW_USEDEFAULT,
//	//	1024, 576,
//	//	WS_OVERLAPPEDWINDOW
//	//);
//
//	// Graphics Module
//	Core::Graphics::GraphicsModule* graphicsModule = new Core::Graphics::GraphicsModule("DirectX11.dll");
//	graphicsModule->GetGraphics()->CreateRenderer(iWindow, &mainSystem->m_Renderer); // 描画領域の設定
//
//
//	//###################################################################################
//	/**
//	*
//	*	Shader
//	*
//	*/
//#if SHADER_ENABLE
//
//	unsigned long fsize;
//	unsigned char* buffer;
//
//	// 頂点シェーダ設定
//	Platform::Graphics::IVertexShader* vertexShader = nullptr;
//	if (Platform::IO::FileStream::readFileInfo("Default_VertexShader.cso", &fsize, &buffer))
//	{
//		LOG_DEBUG("頂点シェーダ読み込み...");
//		Platform::Graphics::VERTEX_INPUT_LAYOUT layouts[] = {
//			Platform::Graphics::VERTEX_INPUT_LAYOUT::VSIL_POSITION
//		};
//		graphicsModule->GetGraphics()->CreateVertexShader(buffer, fsize, layouts, ARRAYSIZE(layouts), &vertexShader);
//
//		vertexShader->SetShaderResource();
//
//		delete[] buffer;
//	}
//
//	// ピクセルシェーダ設定
//	Platform::Graphics::IPixelShader* pixelShader = nullptr;
//	if (Platform::IO::FileStream::readFileInfo("Default_PixelShader.cso", &fsize, &buffer))
//	{
//		LOG_DEBUG("ピクセルシェーダ読み込み...");
//
//		graphicsModule->GetGraphics()->CreatePixelShader(buffer, fsize, &pixelShader);
//
//		delete[] buffer;
//	}
//
//
//
//#endif
//
//	//###################################################################################
//	/**
//	*
//	*	Constant
//	*
//	*/
//#if SHADER_ENABLE
//
//	Platform::Graphics::IConstantBuffer* constantBuf = nullptr;
//
//	graphicsModule->GetGraphics()->CreateConstantBuffer(sizeof(Core::Matrix4x4), sizeof(float), &constantBuf);
//	if (constantBuf != nullptr)
//	{
//		Core::Matrix4x4 matrix;
//		matrix.m[0][0] = 10.0f;
//		matrix.m[0][1] = 5.0f;
//		matrix.m[0][2] = 10.0f;
//		constantBuf->UpdateBufferResource(&matrix);
//
//	}
//
//#endif
//
//	//###################################################################################
//	/**
//	*
//	*	VertexBuffer
//	*
//	*/
//#if 1
//
//	Platform::Graphics::IVertexBuffer* vertexBuffer;
//
//	MESH_VERTEX vertex[] = {
//		{{-1.0f,0.0f, 1.0f},{0.0f,1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f}},
//		{{ 1.0f,0.0f, 1.0f},{0.0f,1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f},{1.0f,0.0f}},
//		{{-1.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,1.0f}},
//		{{ 1.0f,0.0f,-1.0f},{0.0f,1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f},{1.0f,1.0f}},
//	};
//
//	graphicsModule->GetGraphics()->CreateVertexBuffer(vertex, sizeof(MESH_VERTEX), ARRAYSIZE(vertex), &vertexBuffer);
//	graphicsModule->GetGraphics()->ReleaseVertexBuffer(&vertexBuffer);
//#endif
//
//	//###################################################################################
//	/**
//	*
//	*	IndexBuffer
//	*
//	*
//	*/
//#if 1
//
//	Platform::Graphics::IIndexBuffer* indexBuffer;
//
//	unsigned int indexes[] = { 0,1,2, 1,3,2 };
//
//	graphicsModule->GetGraphics()->CreateIndexBuffer(indexes,sizeof(unsigned int),ARRAYSIZE(indexes),&indexBuffer);
//	graphicsModule->GetGraphics()->ReleaseIndexBuffer(&indexBuffer);
//
//#endif
//
//	/**
//	* 
//	*	Meshの描画
//	*	・VertexShader
//	*	・IndexShader
//	*	・ConstantBuffer
//	*	・VertexBuffer
//	*	・IndexBuffer
//	*	各登録
//	* 
//	*	RendererにMesh描画をする仕組みが必要
//	*	
//	*/
//
//
//
//
//	//###################################################################################
//	/**
//	*
//	*	Network
//	*
//	*/
//#if NETWORK_ENABLE
//
//	Core::Network::NetworkModule networkModule("Winsock.dll");
//	::Platform::Network::detail::INetwork* network;
//	networkModule.CreateNetwork(&network);
//
//	network->Startup();
//
//	// Thread
//	Core::Thread server([network]() {
//		::Platform::Network::detail::ISocket* iSocket = nullptr;
//
//		::Platform::Network::SocketInfo info;
//		info.m_address = NULL;
//		info.m_port = "27015";
//		info.m_flags = ::Platform::Network::Flags::PASSIVE;
//
//		if (network->Create(&iSocket, info) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//		if (network->Bind(iSocket) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		if (network->Listen(iSocket) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		::Platform::Network::detail::ISocket* iClient = nullptr;
//
//		if (network->Accept(iSocket, &iClient) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		network->Release(&iSocket);
//
//		int iResult = 0;
//		char buf[256];
//		do
//		{
//			LOG_DEBUG("Server Idle");
//			iResult = network->Recv(iClient, buf, 256);
//			if (iResult > 0)
//			{
//				int send = network->Send(iClient, buf, iResult);
//				if (send == Platform::Network::FAILED) {
//					network->Release(&iClient);
//					return;
//				}
//				buf[send] = '\0';
//				LOG_DEBUG("Recived Message : %s", buf);
//				break;
//			}
//			else if (iResult == 0)
//			{
//
//			}
//			else
//			{
//				break;
//			}
//		} while (iResult > 0);
//
//		network->Close(iClient, ::Platform::Network::CloseType::BOTH);
//		network->Release(&iClient);
//
//		LOG_DEBUG("Server Thread End");
//		});
//
//	Core::Thread client([network]() {
//		std::this_thread::sleep_for(Core::Time::Seconds(3));
//
//		::Platform::Network::detail::ISocket* iSocket = nullptr;
//
//		::Platform::Network::SocketInfo info;
//		info.m_address = "localhost";
//		info.m_port = "27015";
//
//		if (network->Create(&iSocket, info) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		if (network->Connect(iSocket) == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		char buf[256];
//		const char* sendbuf = "this is a test";
//		int iResult = 0;
//		iResult = network->Send(iSocket, sendbuf, (int)strlen(sendbuf));
//		if (iResult == Platform::Network::FAILED) {
//			network->Release(&iSocket);
//			return;
//		}
//
//		do
//		{
//			LOG_DEBUG("Client Idle");
//			iResult = network->Recv(iSocket, buf, 256);
//} while (iResult > 0);
//
//network->Close(iSocket, ::Platform::Network::CloseType::SEND);
//network->Release(&iSocket);
//
//LOG_DEBUG("Client Thread End");
//		});
//
//#endif
//
//	// MainLoop
//	mainSystem->mainLoop();
//
//
//#if NETWORK_ENABLE
//
//	client.run();
//	server.run();
//
//	network->Cleanup();
//
//	networkModule.ReleaseNetwork(&network);
//
//#endif
//
//#if SHADER_ENABLE
//
//	graphicsModule->GetGraphics()->ReleaseVertexShader(&vertexShader);
//	graphicsModule->GetGraphics()->ReleasePixelShader(&pixelShader);
//
//	graphicsModule->GetGraphics()->ReleaseConstantBuffer(&constantBuf);
//
//#endif
//
//	graphicsModule->GetGraphics()->ReleaseRenderer(&mainSystem->m_Renderer);
//
//
//	delete mainSystem;
//	delete graphicsModule;
//
//	return 0;
//