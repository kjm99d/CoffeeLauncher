#pragma once
#include "Common.h"

#if __cplusplus
extern "C" {
#endif
    /**
     * @brief 프로세스 ID를 사용하여 윈도우 핸들을 구하는 함수.
     *
     * @param dwPID - Process ID 값.
     *
     * @return HANDLE - 핸들 값
     */
    COFFEEPROCSEARCH_API HANDLE GetWindowHandleFromPID(DWORD dwPID);


    /**
     * @brief 프로세스 아이디를 통해 해당 프로세스가 64비트 프로세스 인지 확인 한다.
     *
     *  @param dwPID - Process ID 값.
     *
     * @return BOOL - 64비트 프로세스 여부
     */
    COFFEEPROCSEARCH_API BOOL IsX64Process(DWORD dwPID);


#if __cplusplus
}
#endif

