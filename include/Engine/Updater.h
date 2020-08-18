#pragma once
#ifndef UPDATER_H
#define UPDATER_H

namespace Engine
{
	/**
	* @class    IUpdater
	* @brief    XVˆ—
	*/
	class IUpdater
	{
	private:

	public:
		IUpdater() {};
		virtual ~IUpdater() {};

		virtual void Update() = 0;

	};//class IUpdater

}//namespace Engine

#endif //ifndef UPDATER_H