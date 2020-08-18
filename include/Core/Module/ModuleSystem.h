#pragma once
#ifndef MODULE_SYSTEM_H
#define MODULE_SYSTEM_H

#include<map>
#include<vector>

namespace Core
{
	/**
	* @class    ModuleSystem
	* @brief    IModuleÇìoò^é¿çsÇ∑ÇÈSystem
	*/
	class ModuleSystem
	{
		using ModuleIndex = std::vector<detail::IModule*>;
	protected:
		std::map<ModuleType, ModuleIndex> m_Modules {
			{ModuleType::Initialize,ModuleIndex()},
			{ModuleType::Update,ModuleIndex()},
			{ModuleType::Render,ModuleIndex()},
			{ModuleType::Finalize,ModuleIndex()}
		};

	private:
		void removeAtModules(ModuleIndex* index,detail::IModule* Module);

	public:
		ModuleSystem();
		virtual ~ModuleSystem();

		virtual void RegisterModule(detail::IModule* Module);
		virtual void UnRegisterModule(detail::IModule* Module);

		virtual void ProcessModule(ModuleType type);

	};//class ModuleSystem

}//namespace Core

#endif