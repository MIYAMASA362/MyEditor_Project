#include "Config.h"

#include "Platform/Module/Module.h"

#include "Core/Thread/Thread.h"
#include "Core/System/ISystemModule.h"
#include "Core/System/ProcessModule.h"

namespace Core
{
	ProcessModule::ProcessModule(Core::System::ModuleType type, void (*process)(void))
		:
		ISystemModule(type),
		m_Process(process)
	{

	}
	ProcessModule::~ProcessModule()
	{
	}
	void ProcessModule::behaviour()
	{
		m_Process();
	}
}// namespace Core

