#pragma once
#ifndef CORE_PROCESS_MODULE_H
#define CORE_PROCESS_MODULE_H

#include<functional>

namespace Core
{
	class ProcessModule : public Core::System::ISystemModule
	{
	private:

	public:
		ProcessModule(Core::System::ModuleType type,void (*process)(void));
		virtual ~ProcessModule();

		virtual void behaviour() override;

	};// class ProcessModule

}// namespace Core
#endif // ifndef CORE_PROCESS_MODULE_H

