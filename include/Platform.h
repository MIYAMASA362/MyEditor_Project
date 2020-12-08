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

// Platform Interface
#include"Platform/Base/ISystem.h"
#include"Platform/Base/IWindow.h"
#include"Platform/Base/IRenderer.h"
#include"Platform/Base/INetwork.h"

// Platform IO
#include"Platform/IO/DllLoader.h"
#include"Platform/IO/Stream.h"
#include"Platform/IO/FileStream.h"
#include"Platform/IO/Path.h"
#include"Platform/IO/PathHelper.h"

// Platform Module
#include"Platform/Module/Module.h"

// Platform 
#if defined(ENGINE_WIN32)
#include"Platform/Windows/Window.h"
#pragma comment(lib,"Windows.lib")

#endif //if defined(ENGINE_WIN32)

#pragma comment(lib,"Platform.lib")


#endif //ifndef PLATFORM_H