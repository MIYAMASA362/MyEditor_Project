#define ENGINE_DIRECTX11
#define ENGINE_WINSOCK

// �L���t���O
#define NETWORK_ENABLE 0


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
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//###################################################################################
	/**
	*
	*	FileStream
	*
	*
	*/
#if 0

	Platform::IO::FileStream* stream;
	Platform::IO::FileStream::create("StreamTest.txt", Platform::IO::FileMode::ReadWrite, &stream);

	stream->writeFormat("[Initialize]\n[Update]\n[Renderer]\n[Finalize]");
	stream->seek(10, Platform::IO::StreamSeek::Begin);

	stream->seekFind("[Update]");
	std::string str(100, '\0');
	stream->read(str);

	stream->close();
	delete stream;

	Platform::IO::DllLoader GraphicLoder;
	GraphicLoder.getProcess(TO_STRING(Platform::Graphics::DX11Graphics));

#endif

	//###################################################################################
	/**
	*
	*	OpenGL�Ȃǂ̃V�F�[�_�ɓƎ��Ή����邽�߂ɂ́A�Ǝ��̃V�F�[�_��`�t�H�[�}�b�g�t�@�C�����쐬����K�v������
	*	�Ǝ��̃V�F�[�_����HLSL�𒊏o���Ē�`�A�����R���p�C����cso�Ȃǂ̃��\�[�X��f���o���B
	*	�܂��͓����Ŋm�ہE�B�؂����Ă���
	*
	*	HLSL �R���p�C�� fxc.exe (SDK/utility/bin/x86)
	*
	*	�Ǝ��̃V�F�[�_�t�@�C�����v���R���p�C��������ۂɗ��p����
	*	�G�t�F�N�g�t�@�C���̉B�؂��Ȃǂɗ��p�ł���\��������̂ŗv�m�F
	*
	*	Qiita : HLSL�̃I�t���C���R���p�C�����ɋC��t���邱��
	*	�Ehttps://qiita.com/shiro_naga/items/c1bac277df82fdd8bf52
	*	�E
	*
	*/
#if 0
	char path[MAX_PATH + 1];
	strcpy_s(path, curDir);

	// fx�t�@�C��
	system("C:\\Users\\MIYAM\\Desktop\\MyEditor_Project\\external\\fxc.exe TestShader.hlsl /T fx_5_0 /Fo Test.cfx");

#endif

	// Engine
	Engine::System* mainSystem = new Engine::System();

	// Platform
	Platform::detail::IWindow* iWindow;
	iWindow = new Platform::Windows::Window(
		hInstance,
		(LPSTR)"MainWindow",
		(LPSTR)"MainWindow",
		CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 576,
		WS_OVERLAPPEDWINDOW
	);

	// Graphics Module
	Core::Graphics::GraphicsModule* graphicsModule = new Core::Graphics::GraphicsModule("DirectX11.dll");
	graphicsModule->GetGraphics()->CreateRenderer(iWindow, &mainSystem->m_Renderer); // �`��̈�̐ݒ�


	//###################################################################################
	/**
	*
	*	Shader
	*
	*/
#if 0

	unsigned long fsize;
	unsigned char* buffer;

	// ���_�V�F�[�_�ݒ�
	Platform::Graphics::IVertexShader* vertexShader = nullptr;
	if (Platform::IO::FileStream::readFileInfo("Default_VertexShader.cso", &fsize, &buffer))
	{
		LOG_DEBUG("���_�V�F�[�_�ǂݍ���...");
		Platform::Graphics::VERTEX_INPUT_LAYOUT layouts[1];

		layouts[0] = Platform::Graphics::VERTEX_INPUT_LAYOUT::VSIL_POSITION;

		graphicsModule->GetGraphics()->CreateVertexShader(buffer, fsize, layouts, 1, &vertexShader);
		graphicsModule->GetGraphics()->ReleaseVertexShader(&vertexShader);

		delete[] buffer;
	}

	// �s�N�Z���V�F�[�_�ݒ�
	Platform::Graphics::IPixelShader* pixelShader = nullptr;
	if (Platform::IO::FileStream::readFileInfo("Default_PixelShader.cso", &fsize, &buffer))
	{
		LOG_DEBUG("�s�N�Z���V�F�[�_�ǂݍ���...");

		graphicsModule->GetGraphics()->CreatePixelShader(buffer, fsize, &pixelShader);
		graphicsModule->GetGraphics()->ReleasePixelShader(&pixelShader);

		delete[] buffer;
	}



#endif

	//###################################################################################
	/**
	*
	*	Network
	*
	*/
#if NETWORK_ENABLE

	Core::Network::NetworkModule networkModule("Winsock.dll");
	::Platform::Network::detail::INetwork* network;
	networkModule.CreateNetwork(&network);

	network->Startup();

	// Thread
	Core::Thread server([network]() {
		::Platform::Network::detail::ISocket* iSocket = nullptr;

		::Platform::Network::SocketInfo info;
		info.m_address = NULL;
		info.m_port = "27015";
		info.m_flags = ::Platform::Network::Flags::PASSIVE;

		if (network->Create(&iSocket, info) == Platform::Network::FAILED) {
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

		if (network->Accept(iSocket, &iClient) == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		network->Release(&iSocket);

		int iResult = 0;
		char buf[256];
		do
		{
			LOG_DEBUG("Server Idle");
			iResult = network->Recv(iClient, buf, 256);
			if (iResult > 0)
			{
				int send = network->Send(iClient, buf, iResult);
				if (send == Platform::Network::FAILED) {
					network->Release(&iClient);
					return;
				}
				buf[send] = '\0';
				LOG_DEBUG("Recived Message : %s", buf);
				break;
			}
			else if (iResult == 0)
			{

			}
			else
			{
				break;
			}
		} while (iResult > 0);

		network->Close(iClient, ::Platform::Network::CloseType::BOTH);
		network->Release(&iClient);

		LOG_DEBUG("Server Thread End");
		});

	Core::Thread client([network]() {
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
		iResult = network->Send(iSocket, sendbuf, (int)strlen(sendbuf));
		if (iResult == Platform::Network::FAILED) {
			network->Release(&iSocket);
			return;
		}

		do
		{
			LOG_DEBUG("Client Idle");
			iResult = network->Recv(iSocket, buf, 256);
		} while (iResult > 0);

		network->Close(iSocket, ::Platform::Network::CloseType::SEND);
		network->Release(&iSocket);

		LOG_DEBUG("Client Thread End");
		});

#endif

	// MainLoop
	mainSystem->mainLoop();


#if NETWORK_ENABLE

	client.run();
	server.run();

	network->Cleanup();

	networkModule.ReleaseNetwork(&network);

#endif

	graphicsModule->GetGraphics()->ReleaseRenderer(&mainSystem->m_Renderer);

	delete mainSystem;
	delete graphicsModule;

	return 0;
}