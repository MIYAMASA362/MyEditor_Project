#pragma once
#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

namespace Engine
{
	namespace Internal
	{
		namespace detail
		{
			/**
			* @class    IEntity
			* @brief    ���G���e�B�e�B
			*/
			class IEntity
			{
			public:
				IEntity() = default;
				virtual ~IEntity() = default;

			private:


			};// class IEntity

		}// namespace Engine::Internal::detail
	} // namespasce Engine::Internal
}// namespace Engine

namespace Engine
{
	namespace Internal
	{
		/**
		* @class    Entity
		* @brief    �G���e�B�e�B
		*/
		class Entity : public detail::IEntity
		{
		public:


		};// class Entity

	}// namespace Engine::Internal
}// namespace Engine

#endif // ifndef ENGINE_ENTITY_H