#pragma once
#ifndef CORE_GRAPHICSFACTOR_H
#define CORE_GRAPHICSFACTOR_H

namespace Core
{
	namespace Graphics
	{
		/**
		* @class    IGraphicsFactory
		* @brief	
		*/
		class ENGINE_API IGraphicsFactory
		{
			//static_assert(std::is_base_of<Platform::detail::IRenderer,Type>::value,"Type must inherit form IRenderer");
		public:
			using Value_Type = ::Platform::Graphics::detail::IRenderer;

			IGraphicsFactory() {};
			virtual ~IGraphicsFactory() {};

		public:
			virtual void create(HWND hWnd, Value_Type** output) = 0;
			virtual void release(Value_Type** instance) = 0;

		};// class IGraphicsFactory

	}// namespace Core::Graphics
}// namespace Core

#endif //ifndef CORE_GRAPHICSFACTORY_H