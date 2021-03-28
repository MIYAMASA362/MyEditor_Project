#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

// Config
#include"Platform/Config.h"

// DesignPattern
#include"Platform/DesignPattern/Singleton.h"
#include"Platform/DesignPattern/Factory.h"

// Platform Base
#include"Platform/Base/BitFlags.h"
#include"Platform/Base/String.h"
#include"Platform/Base/StringHelper.h"
#include"Platform/Base/Logger.h"
#include"Platform/Base/Assert.h"
#include"Platform/Base/Result.h"
#include"Platform/Base/RefObject.h"

// Platform Interface
#include"Platform/Base/IRenderer.h"
#include"Platform/Base/INetwork.h"

// Platform IO
#include"Platform/IO/DllLoader.h"
#include"Platform/IO/Stream.h"
#include"Platform/IO/FileStream.h"
#include"Platform/IO/Path.h"
#include"Platform/IO/PathHelper.h"

// Platform 
#if defined(ENGINE_WIN32)

#endif //if defined(ENGINE_WIN32)

#pragma comment(lib,"Platform.lib")


#endif //ifndef PLATFORM_H