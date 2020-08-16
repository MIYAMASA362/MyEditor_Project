#pragma once
#ifndef CORE_H
#define CORE_H

// Core Common
#include"Core/Common.h"

// Core Base
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
#include"Core/IO/Common.h"
#include"Core/IO/FileStream.h"

#endif // ifndef CORE_H