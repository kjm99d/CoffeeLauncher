#pragma once
#include "Common.h"

#define INT_INJECTION_SUCCESS   1
#define INT_OPENPROCESS_FAIL    -10
#define INT_LOADLIBRARY_FAIL    -20
#define INT_GETPROCADDRESS_FAIL -30
#define INT_VIRTUALALLOC_FAIL   -40
#define INT_WRITEPROCESSMEMORY_FAIL     -50
#define INT_CREATEREMOTETHREAD_FAIL     -60

/**
 * @brief 프로젝트에 DLL을 인젝션 하는 함수
 * @param dwPid - 프로세스 ID
 * @param pDllPath - DLL의 경로
 * @return 성공여부 성공 시 INT_INJECTION_SUCCESS(1)
 */
COFFEEPROCSEARCH_API int Inject(const DWORD dwPid, const char* pDllPath);
COFFEEPROCSEARCH_API int InjectXP(const DWORD dwPid, const char* pDllPath);




