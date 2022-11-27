#pragma once
#include "Common.h"

#include <vector>

#if __cplusplus
extern "C" {
#endif
    /**
     * @brief 프로세스 ID를 사용하여 프로세스 존재 여부를 구하는 함수.
     *
     * @param dwPID - Process ID 값.
     *
     * @return BOOL - 찾은 여부
     */
    COFFEEPROCSEARCH_API BOOL FindProcessFromID(DWORD dwPID);

    /**
     * @brief 프로세스 ID를 사용하여 프로세스 존재 여부를 구하는 함수.
     * 
     * @param dwPID - Process Name
     *
     * @return BOOL - 찾은 여부
     */
    COFFEEPROCSEARCH_API BOOL FindProcessByName(char * strProcessName);


    /**
     * @brief 프로세스 아이디를 통해 해당 프로세스가 64비트 프로세스 인지 확인 한다.
     *
     *  @param dwPID - Process ID 값.
     *
     * @return BOOL - 64비트 프로세스 여부
     */
    COFFEEPROCSEARCH_API BOOL IsX64Process(DWORD dwPID);


    COFFEEPROCSEARCH_API BOOL GetProcessIdFromName(const char * pProcessName, std::vector<DWORD> * pids);


#if __cplusplus
}
#endif

