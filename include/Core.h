#pragma once
#ifndef CORE_H
#define CORE_H

// Core Base

// Allocator
#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/LinerAllocator.h"
#include"Core/Allocator/StackAllocator.h"
#include"Core/Allocator/PoolAllocator.h"
#include"Core/Allocator/DoubleBufferAllocator.h"

// Types
#include"Core/Types/Color.h"

// Math
#include"Core/Types/Math.h"
#include"Core/Types/Matrix.h"
#include"Core/Types/Quaternion.h"
#include"Core/Types/Vector2.h"
#include"Core/Types/Vector3.h"
#include"Core/Types/Vector4.h"

#include"Core/System/Window.h"
#include"Core/Thread/Thread.h"
#include"Core/Time/Time.h"

// Lib
#pragma comment(lib,"Core.lib")

#endif // ifndef CORE_H