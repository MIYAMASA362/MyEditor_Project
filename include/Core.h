#pragma once
#ifndef CORE_H
#define CORE_H

// Core Base
#include"Core/Base/BitFlags.h"
#include"Core/Base/Logger.h"
#include"Core/Base/Assert.h"
#include"Core/Base/Result.h"

// Allocator
#include"Core/Allocator/IAllocator.h"
#include"Core/Allocator/LinerAllocator.h"
#include"Core/Allocator/StackAllocator.h"
#include"Core/Allocator/PoolAllocator.h"
#include"Core/Allocator/DoubleBufferAllocator.h"

// IO
#include"Core/IO/Stream.h"
#include"Core/IO/FileStream.h"
#include"Core/IO/Path.h"
#include"Core/IO/DllLoader.h"

// Factory
#include"Core/Graphics/GraphicsFactory.h"

// Module
#include"Core/Module/Module.h"
#include"Core/Graphics/GraphicsModule.h"

// Graphics
#include"Core/Graphics/Renderer.h"

// System
#include"Core/System/System.h"


// Lib
#pragma comment(lib,"Core.lib")

#endif // ifndef CORE_H