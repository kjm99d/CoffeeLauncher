#include "OS.h"
#include <stdio.h>

typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

BOOL OS::Is64Bit()
{
#ifdef _WIN64
    return TRUE;
#else
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
    if (fnIsWow64Process && 0 == fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
    {
        printf("HANDLE IS NOT FOUND");
    }
    return bIsWow64;
#endif
}


#if 0
BOOL OS::Is64BitProcess(DWORD dwPID)
{

    HANDLE hProcess = 0;
    BOOL bIsWow64 = false;
    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");
    if (fnIsWow64Process && fnIsWow64Process(hProcess, &bIsWow64))
    {
        bIsWow64 = ~bIsWow64;
    }
    else
    {
        // 함수 포인터를 찾았고, 호출의 결과가 실패인 경우 에러로 판단한다.
    }

    return bIsWow64;

}
#endif

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
