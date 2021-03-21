#pragma once
#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

namespace Core
{
	namespace System
	{
		class ISystemModule;

		/**
		* @class    ISystem
		* @brief    ƒVƒXƒeƒ€‚ÌŠîŠ²
		*/
		class ISystem
		{
			using ModuleIndex = std::vector<ISystemModule*>;
		private:
			void removeAtModules(ModuleIndex* index, ISystemModule* iModule);

		protected:
			std::map<ModuleType,ModuleIndex> m_Modules{
				{ModuleType::Initialize,ModuleIndex()},
				{ModuleType::Update,ModuleIndex()},
				{ModuleType::Render,ModuleIndex()},
				{ModuleType::Finalize,ModuleIndex()}
			};

		public:
			ISystem();
			virtual ~ISystem();

			virtual void RegisterModule(ISystemModule* iModule);
			virtual void UnRegisterModule(ISystemModule* iModule);

			virtual void ProcessModule(ModuleType type);

			virtual int mainLoop() ENGINE_PURE;

		};// class ISystem

	}// namespace Core::System
}// namespace Core

#endif// ifndef CORE_SYSTEM_H