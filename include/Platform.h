#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

// Config
#include"Platform/Config.h"

// DesignPattern
#include"Platform/DesignPattern/Singleton.h"
#include"Platform/DesignPattern/Factory.h"

// Platform Base
#include"Platform/Base/ISystem.h"
#include"Platform/Base/IWindow.h"
#include"Platform/Base/IRenderer.h"
#include"Platform/Network/INetwork.h"

// Platform 
#if defined(ENGINE_WIN32)
#include"Platform/Windows/Window.h"
#pragma comment(lib,"Windows.lib")

#endif //if defined(ENGINE_WIN32)

#pragma comment(lib,"Platform.lib")


#endif //ifndef PLATFORM_H