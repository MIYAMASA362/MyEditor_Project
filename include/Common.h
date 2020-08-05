#pragma once
#ifndef COMMON_H
#define COMMON_H

// ENGINE_APIの無効フラグ 
#define NO_EXPORT

// Loggerの機能を無効フラグ Log名前空間の使用禁止
//#define DISABLE_LOGGING


// Debug build flag
#if defined(DEBUG) || defined(_DEBUG)
#define IKETY_DEBUG
#endif

// platform
#include"Platform.h"


#endif