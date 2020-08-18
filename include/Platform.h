#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include"Platform/Common.h"

#include"Platform/Base/ISystem.h"
#include"Platform/Base/IWindow.h"

#if defined(ENGINE_WIN32)
#include"Platform/Windows/Window.h"

#endif //if defined(ENGINE_WIN32)

#endif //ifndef PLATFORM_H