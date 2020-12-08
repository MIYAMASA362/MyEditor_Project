#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <map>

#include"Platform/Base/ISystem.h"
#include"Platform/Module/Module.h"

#include"Core/System/System.h"

namespace Core
{
	namespace System
	{
		void ISystem::removeAtModules(ModuleIndex * index, ISystemModule * iModule)
		{
			index->erase(std::remove(index->begin(), index->end(), iModule), index->end());
		}

		ISystem::ISystem()
		{
		
		}

		ISystem::~ISystem()
		{
			m_Modules.clear();
		}

		void ISystem::RegisterModule(ISystemModule * iModule)
		{
			try
			{
				if ((iModule->m_ModuleType & ModuleType::Initialize) == ModuleType::Initialize) m_Modules.at(ModuleType::Initialize).push_back(iModule);
				if ((iModule->m_ModuleType & ModuleType::Update) == ModuleType::Update) m_Modules.at(ModuleType::Update).push_back(iModule);
				if ((iModule->m_ModuleType & ModuleType::Render) == ModuleType::Render) m_Modules.at(ModuleType::Render).push_back(iModule);
				if ((iModule->m_ModuleType & ModuleType::Finalize) == ModuleType::Finalize) m_Modules.at(ModuleType::Finalize).push_back(iModule);
			}
			catch (std::out_of_range&)
			{
				ASSERT(false, "ModuleSystem:指定されたTypeのModuleIndexがありません。");
			}
		}

		void ISystem::UnRegisterModule(ISystemModule * iModule)
		{
			try
			{
				if ((iModule->m_ModuleType & ModuleType::Initialize) == ModuleType::Initialize) removeAtModules(&m_Modules.at(ModuleType::Initialize), iModule);
				if ((iModule->m_ModuleType & ModuleType::Update) == ModuleType::Update) removeAtModules(&m_Modules.at(ModuleType::Update), iModule);
				if ((iModule->m_ModuleType & ModuleType::Render) == ModuleType::Render) removeAtModules(&m_Modules.at(ModuleType::Render), iModule);
				if ((iModule->m_ModuleType & ModuleType::Finalize) == ModuleType::Finalize) removeAtModules(&m_Modules.at(ModuleType::Finalize), iModule);
			}
			catch (std::out_of_range&)
			{
				ASSERT(false, "ModuleSystem:指定されたTypeのModuleIndexがありません。");
			}
		}

		void ISystem::ProcessModule(ModuleType type)
		{
			try
			{
				auto index = m_Modules.at(type);
				for (auto m : index)
				{
					m->behaviour();
				}
			}
			catch (std::out_of_range&)
			{
				ASSERT(false, "ModuleSystem:指定されたTypeのModuleIndexがありません。");
			}
		}

		// class ISystem
	}// namespace Core:: System

	namespace System
	{
		ISystemModule::ISystemModule(ModuleType type)
			:
			m_ModuleType(type)
		{

		}

		ISystemModule::~ISystemModule()
		{

		}

		// class ISystemModule
	}// namespace Core::System
}// namespace Core
