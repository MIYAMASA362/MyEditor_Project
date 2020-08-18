#pragma once
#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

namespace Core
{
	class CoreSystem
	{
	private:


	public:
		CoreSystem();
		virtual ~CoreSystem();

		virtual void Initialize();
		virtual void Update();
		virtual void Finalize();

	};//class CoreSystem
}//namespace Core

#endif