#include "ProcessMonitor.h"

HANDLE GetWindowHandleFromPID(DWORD dwPID)
{
    const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPID);
    if (NULL == hProcess)
    {
        return NULL;
    }
    else
    {
        return hProcess;
    }
}



BOOL IsX64Process(DWORD dwPID)
{
    BOOL bIsWow64;
    IsWow64Process(GetWindowHandleFromPID(dwPID), &bIsWow64);
    return 0 == bIsWow64;
}
