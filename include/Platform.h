#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include"Platform/Config.h"

#include"Platform/DesignPattern/Singleton.h"

//Platform Base
#include"Platform/Base/ISystem.h"
#include"Platform/Base/IWindow.h"
#include"Platform/Base/IRenderer.h"

//Platform 
#if defined(ENGINE_WIN32)
#include"Platform/Windows/Window.h"

#endif //if defined(ENGINE_WIN32)

//Graphics
#if defined(ENGINE_DIRECTX11)
#include"Platform/Graphics/DirectX11.h"

#endif //if defined(ENGINE_DIRECTX11)

#endif //ifndef PLATFORM_H