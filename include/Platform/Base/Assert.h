#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#ifndef PLATFORM_LOGGER_H
#include"Platform/Base/Logger.h"
#endif

//ÉvÉçÉOÉâÉÄíÜíf
#if defined(ENGINE_DEBUG)
#define ABORT() DebugBreak()
#else
#define ABORT() exit(1)
#endif

#if defined(ENGINE_DEBUG)

#define ASSERT(condition,fmt,...) do{						\
		if(!(condition)){									\
			LOG_ASSERT(fmt,__VA_ARGS__)						\
			ABORT();										\
		}													\
	}while(0)

#define ASSERT_NOT_NULL(pointer,fmt,...) do{				\
		if(!(pointer)){										\
			LOG_ASSERT(fmt,__VA_ARGS__)						\
			ABORT();										\
		}													\
	}while(0)

#else

#define ASSERT(condition,...) ((void)0)

#define ASSERT_NOT_NULL(pointer,...) ((void)0)

#endif

#endif // ifndef ASSERT_H