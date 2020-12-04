#pragma once
#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

/****************************************************************
*	Macro that Change Config
*****************************************************************/

// Loggerの機能を無効フラグ Log名前空間の使用禁止
//#define DISABLE_LOGGING

/****************************************************************
*	Debug Macro
*****************************************************************/

// Debug build flag
#if defined(DEBUG) || defined(_DEBUG)
#define ENGINE_DEBUG
#endif

/****************************************************************
*	Export Macro
*****************************************************************/

// API Export
#if defined(NO_EXPORT)
#define ENGINE_API 
#else
// Declspace macro
#if defined(ENGINE_EXPORT)
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#endif

// EXTERN C
#ifndef EXTERN_C
#define EXTERN_C extern "C"
#endif// ifndef EXTERN_C

/****************************************************************
*	Support Macro
*****************************************************************/

//Variable name to String
#define TO_STRING(variable) #variable
#define NAMEOF(variable) TO_STRING(variable)


/****************************************************************
*	Platform Target Macro
*****************************************************************/

//Platform : Windows
#if defined(_WIN32) || defined(_WIN64)
#define ENGINE_WIN

//Platform Windows 32bit
#if defined(_WIN32)
#define ENGINE_WIN32
#endif

//Platform Windows 64bit
#if defined(_WIN64)
#define ENGINE_WIN64
#endif

#endif //if defined(_WIN32) || defined(_WIN64)

// Check using bit  architecture
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_X64)
#define ENGINE_64BIT 1

#elif defined(_WIN32) && !defined(_WIN64) || defined(_M_IX86)
#define ENGINE_32BIT 1
#endif

/****************************************************************
*	Platform Include
*****************************************************************/

//===============================================================
//	Windows
//===============================================================
#if defined(ENGINE_WIN)

//===============================================================
//	Winsock
//===============================================================

#if defined(ENGINE_WINSOCK)

#include"../Thirdparty/Network/Winsock/Winsock.h"

#endif

#include<Windows.h>
#include<stdint.h>
#include<iostream>

#include<string>

#else //if defined(ENGINE_WIN)
//===============================================================
//	other
//===============================================================

typedef signed char int8_t:
typedef short int16_t;
typedef int int32_t;
#if defined(ENGINE_64BIT)
typedef long long int64_t;
#endif

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
#if defined(ENGINE_64BIT)
typedef unsigned long long uint64_t;
#endif

typedef float  float_t;
typedef double double_t;

typedef long long intptr_t;
typedef unsigned long long uintptr_t;

#endif //if !defined(ENGINE_WIN)

/****************************************************************
*	Graphics Include
*****************************************************************/

//===============================================================
//	DirectX11
//===============================================================
#if defined(ENGINE_DIRECTX11)

#include"../Thirdparty/Graphics/DirectX11/DirectX11.h"

#endif //if defined(ENGINE_DIRECTX11)

//===============================================================
//	DirectX12
//===============================================================
#if defined(ENGINE_DIRECTX12)

#include"../Thirdparty/Graphics/DirectX12/DirectX12.h"

#endif //if defined(ENGINE_DIRECTX12)

//===============================================================
//	OpenGL
//===============================================================
#if defined(ENGINE_OPENGL)

#include"../Thirdparty/Graphics/OpenGL/OpenGL.h"

#endif //if defined(ENGINE_OPENGL)



/****************************************************************
*	Type
*****************************************************************/

// signed int type
using i8	= int8_t;
using i16	= int16_t;
using i32	= int32_t;
#if defined(ENGINE_64BIT)
using i64	= int64_t;
#else
using i64	= int32_t;
#endif 

// unsigned int type
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
#if defined(ENGINE_64BIT)
using u64 = uint64_t;
#else
using u64 = uint64_t;
#endif

// unsigned float type
using f32 = float_t;
using f64 = double_t;

// pointer
using iptr = intptr_t;
using uptr = uintptr_t;

/****************************************************************
*	EXPLICIT
*****************************************************************/
#define EXPLICIT explicit




#endif	// ifndef PLATFORM_CONFIG_H