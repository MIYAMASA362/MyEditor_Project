#include "stdafx.h"

#include"Platform/Base/IRenderer.h"
#include"Platform/Module/Module.h"

#include"Core/Graphics/GraphicsFactory.h"
#include"Core/Graphics/Renderer.h"

namespace Core
{
	namespace Graphics
	{
		Renderer::Renderer()
		{

		}

		Renderer::~Renderer()
		{

		}

		void Renderer::clear()
		{
			m_Renderer->clear();
		}

		void Renderer::begin()
		{
			m_Renderer->begin();
		}

		void Renderer::end()
		{
			m_Renderer->end();
		}
	}
}