#pragma once
#include "Common.h"
#include <Windows.h>


namespace OS {
    typedef enum {
        kNone,
        kWIN_XP,
        kWIN_VISTA,
        kWIN_7,
        kWIN_8,
        kWIN_8_1,
        kWIN_10,
    } eType;

    COFFEEUTIL_API BOOL Is64Bit();
    COFFEEUTIL_API BOOL Is64Bit(DWORD dwPID);
    COFFEEUTIL_API eType CurrentWindowVersion();
}
