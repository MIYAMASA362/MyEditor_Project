#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

// Debug build flag
#if defined(DEBUG) || defined(_DEBUG)
#define ENGINE_DEBUG
#endif

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

// Platform target macro
#if defined(_WIN32)
#define ENGINE_WIN32
#endif

// Check using bit  architecture
#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_X64)
#define ENGINE_64BIT 1

#elif defined(_WIN32) && !defined(_WIN64) || defined(_M_IX86)
#define ENGINE_32BIT 1
#endif

#include<string>
#include<stdint.h>

#include<Windows.h>
#include<iostream>

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

#define EXPLICIT explicit

#endif	// ifndef PLATFORM_H