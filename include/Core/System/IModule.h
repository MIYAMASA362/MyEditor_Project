#pragma once
#ifndef CORE_MODULE_H
#define CORE_MODULE_H

namespace Platform
{
	namespace IO
	{
		class DllLoader;
	}
}

namespace Core
{
	class IModule
	{
	protected:
		IModule(const char* moduleName);
		virtual ~IModule();

	protected:
		Platform::IO::DllLoader* m_dllLoader;

	};// class IModule

}// namespace Core

#endif // ifndef CORE_MODULE_H