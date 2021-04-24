/****************************************************************************************
*
*	< �ۑ� >
*	1.����v���O���~���O
*	
*	2.�`��V�X�e��
* 
*	3.���\�[�X����
*		���\�[�X�}�l�[�W��
*		�V�F�[�_�H
* 
*	< �w�j >
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
			//	�ȉ���������񏈗�
			//

			// �Q�[���I�u�W�F�N�g�̍X�V

			// �`��
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
//	*	OpenGL�Ȃǂ̃V�F�[�_�ɓƎ��Ή����邽�߂ɂ́A�Ǝ��̃V�F�[�_��`�t�H�[�}�b�g�t�@�C�����쐬����K�v������
//	*	�Ǝ��̃V�F�[�_����HLSL�𒊏o���Ē�`�A�����R���p�C����cso�Ȃǂ̃��\�[�X��f���o���B
//	*	�܂��͓����Ŋm�ہE�B�؂����Ă���
//	*
//	*	HLSL �R���p�C�� fxc.exe (SDK/utility/bin/x86)
//	*
//	*	�Ǝ��̃V�F�[�_�t�@�C�����v���R���p�C��������ۂɗ��p����
//	*	�G�t�F�N�g�t�@�C���̉B�؂��Ȃǂɗ��p�ł���\��������̂ŗv�m�F
//	*
//	*	Qiita : HLSL�̃I�t���C���R���p�C�����ɋC��t���邱��
//	*	�Ehttps://qiita.com/shiro_naga/items/c1bac277df82fdd8bf52
//	*	�E
//	*
//	*/
//#if 0
//	char path[MAX_PATH + 1];
//	strcpy_s(path, curDir);
//
//	// fx�t�@�C��
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
//	graphicsModule->GetGraphics()->CreateRenderer(iWindow, &mainSystem->m_Renderer); // �`��̈�̐ݒ�
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
//	// ���_�V�F�[�_�ݒ�
//	Platform::Graphics::IVertexShader* vertexShader = nullptr;
//	if (Platform::IO::FileStream::readFileInfo("Default_VertexShader.cso", &fsize, &buffer))
//	{
//		LOG_DEBUG("���_�V�F�[�_�ǂݍ���...");
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
//	// �s�N�Z���V�F�[�_�ݒ�
//	Platform::Graphics::IPixelShader* pixelShader = nullptr;
//	if (Platform::IO::FileStream::readFileInfo("Default_PixelShader.cso", &fsize, &buffer))
//	{
//		LOG_DEBUG("�s�N�Z���V�F�[�_�ǂݍ���...");
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
//	*	Mesh�̕`��
//	*	�EVertexShader
//	*	�EIndexShader
//	*	�EConstantBuffer
//	*	�EVertexBuffer
//	*	�EIndexBuffer
//	*	�e�o�^
//	* 
//	*	Renderer��Mesh�`�������d�g�݂��K�v
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