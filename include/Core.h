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

// IO

// Factory
#include"Core/Graphics/GraphicsFactory.h"

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