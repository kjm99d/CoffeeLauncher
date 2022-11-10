#include "OS.h"
#include <sysinfoapi.h>

BOOL OS::Is64Bit()
{
    DWORD dwPid = GetCurrentProcessId();

    return Is64Bit(dwPid);
}

BOOL OS::Is64Bit(DWORD dwPID)
{
    HANDLE hWnd = 0;
    if (GetCurrentProcessId() == dwPID)
    {
        hWnd = GetCurrentProcess();
    }
    else
    {
        OutputDebugString(L"Not Implementation yet !");
    }

    BOOL bWow64 = false;
    // 반환값이 0이 아니면 함수 동작의 성공 여부
    // 매개변수로 들어가는 BOOL 데이터에 대한 정보는 성공여부 0 == 64bit os
    BOOL bFnx64Proc = IsWow64Process(hWnd, &bWow64);
    if (FALSE == bFnx64Proc)
    {
        DWORD dwErr = GetLastError();
    }
    // MSDN 참조
    // 성공인 경우 0을 리턴함
    bWow64 = (bWow64 == 0);

    return bWow64;
}

OS::eType OS::CurrentWindowVersion()
{
    double ret = 0.0;
    NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
    OSVERSIONINFOEXW osInfo;

    *(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");

    if (NULL != RtlGetVersion)
    {
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        RtlGetVersion(&osInfo);
        ret = (double)osInfo.dwMajorVersion;
    }

    if (osInfo.dwMajorVersion == 10 && osInfo.dwMinorVersion == 0)
    {
        return kWIN_10;
    }
    else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 3)
    {
        return kWIN_8_1;
    }
    else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 2)
    {
        return kWIN_8;
    }
    else if (osInfo.dwMajorVersion == 6 && osInfo.dwMinorVersion == 1)
    {
        return kWIN_7;
    }

    return kNone;
    
}
