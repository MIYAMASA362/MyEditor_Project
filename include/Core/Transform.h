#pragma once
#ifndef CORE_TRANSFORM_H
#define CORE_TRANSFORM_H

namespace Core
{
	class Transform final
	{
	protected:
		Vector3 m_Position;
		Quaternion m_Rotation;
		Vector3 m_Scale;

	public:
		Transform();
		~Transform();

	};// class Transform

}// namespace Core

#endif // ifndef CORE_TRANSFORM_H