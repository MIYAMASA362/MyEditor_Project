#pragma once
#ifndef CORE_COLOR_H
#define CORE_COLOR_H

namespace Core
{
	struct Color
	{
		union
		{
			float f[4];
			struct { float r, g, b, a; };
		};

	};// struct Color

}// namespace Core

#endif // ifndef CORE_COLOR_H