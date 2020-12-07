#pragma once
#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

namespace Engine
{
	namespace detail
	{
		class IObject
		{
		public:
			IObject() = default;
			virtual ~IObject() = default;

		};// class IObject

	}// namespace Engine::detail
}// namespace Engine

#endif // ifndef ENGINE_OBJECT_H
