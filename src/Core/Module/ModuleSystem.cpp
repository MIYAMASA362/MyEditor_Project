#include"stdafx.h"
#include<algorithm>

#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"
#include"Core/Module/Module.h"
#include"Core/Module/ModuleSystem.h"

namespace Core
{
	void ModuleSystem::removeAtModules(ModuleIndex* index, detail::IModule * Module)
	{
		index->erase(std::remove(index->begin(),index->end(),Module),index->end());
	}

	ModuleSystem::ModuleSystem()
	{

	}

	ModuleSystem::~ModuleSystem()
	{
		m_Modules.clear();
	}

	void ModuleSystem::RegisterModule(detail::IModule * Module)
	{
		try
		{
			if ((Module->m_ModuleType & ModuleType::Initialize) == ModuleType::Initialize) m_Modules.at(ModuleType::Initialize).push_back(Module);
			if ((Module->m_ModuleType & ModuleType::Update) == ModuleType::Update) m_Modules.at(ModuleType::Update).push_back(Module);
			if ((Module->m_ModuleType & ModuleType::Render) == ModuleType::Render) m_Modules.at(ModuleType::Render).push_back(Module);
			if ((Module->m_ModuleType & ModuleType::Finalize) == ModuleType::Finalize) m_Modules.at(ModuleType::Finalize).push_back(Module);
		}
		catch(std::out_of_range&)
		{
			ASSERT(false, "ModuleSystem:指定されたTypeのModuleIndexがありません。");
		}
	}

	void ModuleSystem::UnRegisterModule(detail::IModule * Module)
	{
		try
		{
			if ((Module->m_ModuleType & ModuleType::Initialize) == ModuleType::Initialize) removeAtModules(&m_Modules.at(ModuleType::Initialize), Module);
			if ((Module->m_ModuleType & ModuleType::Update) == ModuleType::Update) removeAtModules(&m_Modules.at(ModuleType::Update), Module);
			if ((Module->m_ModuleType & ModuleType::Render) == ModuleType::Render) removeAtModules(&m_Modules.at(ModuleType::Render), Module);
			if ((Module->m_ModuleType & ModuleType::Finalize) == ModuleType::Finalize) removeAtModules(&m_Modules.at(ModuleType::Finalize), Module);
		}
		catch(std::out_of_range&)
		{
			ASSERT(false, "ModuleSystem:指定されたTypeのModuleIndexがありません。");
		}
	}

	void ModuleSystem::ProcessModule(ModuleType type)
	{
		try
		{
			auto index = m_Modules.at(type);
			for(auto m : index)
			{
				m->behaviour();
			}
		}
		catch(std::out_of_range&)
		{
			ASSERT(false,"ModuleSystem:指定されたTypeのModuleIndexがありません。");
		}
	}

}//namespace Core