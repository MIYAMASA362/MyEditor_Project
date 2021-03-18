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

// Math
#include"Core/Math/Math.h"
#include"Core/Math/Matrix.h"
#include"Core/Math/Quaternion.h"
#include"Core/Math/Vector2.h"
#include"Core/Math/Vector3.h"
#include"Core/Math/Vector4.h"

#include "Core/Thread/Thread.h"
#include "Core/Time/Time.h"

// IO

// Factory

// Module
#include"Core/Graphics/GraphicsModule.h"
#include"Core/Network/NetworkModule.h"

// Graphics
#include"Core/Graphics/Renderer.h"

// System
#include"Core/System/System.h"


// Lib
#pragma comment(lib,"Core.lib")

#endif // ifndef CORE_H