#include "stdafx.h"

#include"Platform/Base/IResource.h"
#include"Platform/Base/IShader.h"

#include"Thirdparty/Graphics/DirectX11/DirectX11.h"
#include"Thirdparty/Graphics/DirectX11/Graphics.h"

#include "Thirdparty/Graphics/DirectX11/Shader.h"


namespace Platform
{
	namespace Graphics
	{
		VertexShader::VertexShader(
			ID3D11Device* pDevice,
			const void* buffer,
			const unsigned long size,
			VERTEX_INPUT_LAYOUT* inputLayout,
			unsigned int layoutSize
		) :
			m_Source(nullptr),
			m_Layout(nullptr)
		{
			DX11Graphics::GetDevice()->CreateVertexShader(buffer, size, NULL, &m_Source);

			//入力レイアウト設定

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

			DX11Graphics::GetDevice()->CreateInputLayout(layout, layoutSize, buffer, size, &m_Layout);

			delete[] layout;


		}

		VertexShader::~VertexShader()
		{
			ASSERT(m_Source == nullptr, "リソースの解放がされていません。");
			ASSERT(m_Layout == nullptr, "リソースの解放がされていません。");
		}

		void VertexShader::SetShaderResource()
		{
			DX11Graphics::GetImmediateContext()->VSSetShader(m_Source, NULL, 0);
		}

		void VertexShader::SetInputLayout()
		{
			DX11Graphics::GetImmediateContext()->IASetInputLayout(m_Layout);
		}

		void VertexShader::Release()
		{
			if (m_Layout) {
				m_Layout->Release();
				m_Layout = nullptr;
			}
			if (m_Source) {
				m_Source->Release();
				m_Source = nullptr;
			}
		}






		PixelShader::PixelShader(
			ID3D11Device* pDevice,
			const void* buffer,
			const unsigned long size
		) :
			m_Source(nullptr)
		{
			pDevice->CreatePixelShader(buffer, size, NULL, &m_Source);
		}

		PixelShader::~PixelShader()
		{
			ASSERT(m_Source == nullptr, "リソースの解放がされていません。");
		}

		void PixelShader::SetShaderResource()
		{
			DX11Graphics::GetImmediateContext()->PSSetShader(m_Source, NULL, 0);
		}

		void PixelShader::Release()
		{
			if (m_Source)
			{
				m_Source->Release();
				m_Source = nullptr;
			}
		}



	}// namespace Platform::Grpahics
}// namespace Platform