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
    COFFEEUTIL_API eType CurrentWindowVersion();
}



// COFFEEUTIL_API BOOL Is64BitProcess(DWORD dwPID); <<< 얘는 프로세스 정보를 확인하는 용도로 쓰는거니 프로세스 라이브러리로 빠짐