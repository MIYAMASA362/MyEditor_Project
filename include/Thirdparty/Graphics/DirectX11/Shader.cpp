#include "stdafx.h"
#include<io.h>

#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include "Shader.h"


namespace Platform
{
	namespace Graphics
	{
		namespace Shaders
		{
			ConstantBuffer::ConstantBuffer()
			{

			}

			ConstantBuffer::~ConstantBuffer()
			{

			}

			void ConstantBuffer::CreateBuffer()
			{
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = 0;
				desc.MiscFlags = 0;
				desc.StructureByteStride = sizeof(float);

				desc.ByteWidth = sizeof(DirectX::XMMATRIX);
				ID3D11Device* device = DX11Graphics::GetDevice();
				device->CreateBuffer(&desc,NULL,&m_Buffer[BUFFER_LAYOUT::BUFFER_WORLD]);
				device->CreateBuffer(&desc,NULL,&m_Buffer[BUFFER_LAYOUT::BUFFER_VIEW]);
				device->CreateBuffer(&desc,NULL,&m_Buffer[BUFFER_LAYOUT::BUFFER_PROJECTION]);
			}

			void Shader::LoadShaderFile(const char* fileName, unsigned char** buffer, long int* fsize)
			{
				FILE* file;
				file = fopen(fileName, "rb");
				*fsize = _filelength(_fileno(file));

				*buffer = new unsigned char[*fsize];
				fread(*buffer, *fsize, 1, file);
				fclose(file);
			}

			void PixelShader::CreateShader(const char* fileName)
			{
				long int fsize;
				unsigned char* buffer = nullptr;

				LoadShaderFile(fileName,&buffer,&fsize);

				DX11Graphics::GetDevice()->CreatePixelShader(buffer,fsize,NULL,&m_Source);

				delete[] buffer;
			}

			PixelShader::PixelShader()
			{

			}
			PixelShader::~PixelShader()
			{

			}

			VertexShader::VertexShader()
			{

			}
			VertexShader::~VertexShader()
			{

			}


			void VertexShader::CreateShader(const char* fileName, VERTEX_INPUT_LAYOUT* inputLayout, unsigned int layoutSize)
			{
				long int fsize;
				unsigned char* buffer = nullptr;


				LoadShaderFile(fileName, &buffer, &fsize);

				DX11Graphics::GetDevice()->CreateVertexShader(buffer, fsize, NULL, &m_Source);

				//入力レイアウト設定
				{
					D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[layoutSize];

					for (unsigned int i = 0; i < layoutSize; i++)
					{
						D3D11_INPUT_ELEMENT_DESC* target = &layout[i];
						switch (inputLayout[i])
						{
						case VERTEX_INPUT_LAYOUT::VSIL_POSITION:
						{
							target->SemanticName = "POSITION";
							target->SemanticIndex = 0;
							target->Format = DXGI_FORMAT_R32G32B32_FLOAT;
							target->InputSlot = 0;
							target->AlignedByteOffset = 0;
							target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
							target->InstanceDataStepRate = 0;
						}
						break;
						case VERTEX_INPUT_LAYOUT::VSIL_NORMAL:
						{
							target->SemanticName = "NORMAL";
							target->SemanticIndex = 0;
							target->Format = DXGI_FORMAT_R32G32B32_FLOAT;
							target->InputSlot = 0;
							target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
							target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
							target->InstanceDataStepRate = 0;
						}
						break;
						case VERTEX_INPUT_LAYOUT::VSIL_COLOR:
						{
							target->SemanticName = "COLOR";
							target->SemanticIndex = 0;
							target->Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
							target->InputSlot = 0;
							target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
							target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
							target->InstanceDataStepRate = 0;
						}
						break;
						case VERTEX_INPUT_LAYOUT::VSIL_TEXCOORD:
						{
							target->SemanticName = "TEXCOORD";
							target->SemanticIndex = 0;
							target->Format = DXGI_FORMAT_R32G32_FLOAT;
							target->InputSlot = 0;
							target->AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
							target->InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
							target->InstanceDataStepRate = 0;
						}
						break;
						default:
							MessageBox(NULL, "入力レイアウトの要素が欠損してます。", "エラー", MB_OK);
							break;
						}
					}

					DX11Graphics::GetDevice()->CreateInputLayout(layout, layoutSize, buffer, fsize, &m_Layout);

					delete[] layout;

				}

				delete[] buffer;
			}

}// namespace Platform::Grpahics::Shaders
	}// namespace Platform::Grpahics
}// namespace Platform