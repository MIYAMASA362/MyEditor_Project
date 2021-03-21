#include"Config.h"

#include"Platform/Base/ISystem.h"
#include"Platform/Base/IModule.h"

#include"Core/System/ISystemModule.h"

namespace Core
{
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