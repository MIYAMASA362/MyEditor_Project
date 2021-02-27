#include"Config.h"

#include"Core/Math/Vector3.h"
#include"Core/Math/Quaternion.h"

#include"Core/Transform.h"

namespace Core
{
	Transform::Transform()
		:
		m_Position(),
		m_Rotation(),
		m_Scale()
	{
	}

	Transform::~Transform()
	{
	}

}// namespace Core