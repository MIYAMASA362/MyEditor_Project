#pragma once
#ifndef COMMON_H
#define COMMON_H

// ENGINE_API�̖����t���O 
#define NO_EXPORT

// Logger�̋@�\�𖳌��t���O Log���O��Ԃ̎g�p�֎~
//#define DISABLE_LOGGING


// Debug build flag
#if defined(DEBUG) || defined(_DEBUG)
#define IKETY_DEBUG
#endif

// platform
#include"Platform.h"


#endif