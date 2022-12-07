#include "DLLInjector.h"
#include <tlhelp32.h>
#include <stdio.h>

BOOL IsModuleExistInProcessId(DWORD dwPID, char * findModule)
{
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    //  Take a snapshot of all modules in the specified process. 
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        //printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
        return(FALSE);
    }

    //  Set the size of the structure before using it. 
    me32.dwSize = sizeof(MODULEENTRY32);

    //  Retrieve information about the first module, 
    //  and exit if unsuccessful 
    if (!Module32First(hModuleSnap, &me32))
    {
       //printError(TEXT("Module32First"));  // Show cause of failure 
        CloseHandle(hModuleSnap);     // Must clean up the snapshot object! 
        return(FALSE);
    }

    //  Now walk the module list of the process, 
    //  and display information about each module 
    BOOL isFindModule = FALSE;

    do
    {
        wprintf_s(L">> ModuleName [%s] \n", me32.szModule);
        /*
        _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        _tprintf(TEXT("\n     executable     = %s"), me32.szExePath);
        _tprintf(TEXT("\n     process ID     = 0x%08X"), me32.th32ProcessID);
        _tprintf(TEXT("\n     ref count (g)  =     0x%04X"), me32.GlblcntUsage);
        _tprintf(TEXT("\n     ref count (p)  =     0x%04X"), me32.ProccntUsage);
        _tprintf(TEXT("\n     base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        _tprintf(TEXT("\n     base size      = %d"), me32.modBaseSize);
        */

        // 여기에 문자열 비교 할 것.

    } while (Module32Next(hModuleSnap, &me32));

   // _tprintf(TEXT("\n"));

    //  Do not forget to clean up the snapshot object. 
    CloseHandle(hModuleSnap);
    
    return isFindModule;
}

int Inject(const DWORD dwPid, const char* pDllPath, fp_bInjectCallback callback)
{
    int ret = INT_INJECTION_SUCCESS;

    // 콜백 함수를 호출하고 콜백함수가 성공 시 리턴한다.
    if (callback) {
        BOOL bRetCallback = callback();
        if (TRUE == bRetCallback) {
            return FALSE;
        }
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    if (hProcess)
    {
        // DLL 로딩 함수 구하고 
        HMODULE hKernel32 = LoadLibrary(L"Kernel32.dll");
        if (NULL == hKernel32)
        {
            return INT_LOADLIBRARY_FAIL;
        }


        FARPROC lpfnLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");
        if (NULL == lpfnLoadLibrary)
        {
            return INT_GETPROCADDRESS_FAIL;
        }

        // 프로세스 핸들로해서 힙 공간 만들고
        LPVOID dllPathAlloc = VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
        if (NULL == dllPathAlloc)
        {
            printf("Virtual Alloc Failure %d \n", GetLastError());
            return INT_VIRTUALALLOC_FAIL;
        }
        else
        {
            // 메모리 공간 할당에 성공하면
            // 해당 메모리 공간에 문자열 정보 써준다음
            int nLenDLL = strlen(pDllPath);
            DWORD oldProtect = 0;

            if (!WriteProcessMemory(hProcess, dllPathAlloc, pDllPath, nLenDLL, NULL))
            {
                printf("WriteProcessMemory Failure %d \n", GetLastError());

                return INT_WRITEPROCESSMEMORY_FAIL;
            }

            HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpfnLoadLibrary, dllPathAlloc, NULL, NULL);
            if (hThread == NULL)
            {

                printf("CreateRemoteThread Failure %d \n", GetLastError());
                return INT_CREATEREMOTETHREAD_FAIL;
            }



        }
    }
    else
    {
        ret = INT_OPENPROCESS_FAIL;
    }

    return ret;
}

int InjectXP(const DWORD dwPid, const char* pDllPath)
{
    int ret = INT_INJECTION_SUCCESS;

    HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwPid);
    if (hProcess)
    {

        // DLL 로딩 함수 구하고 
        HMODULE hKernel32 = LoadLibrary(L"Kernel32.dll");
        if (NULL == hKernel32)
        {
            return INT_LOADLIBRARY_FAIL;
        }

        FARPROC lpfnLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");
        if (NULL == lpfnLoadLibrary)
        {
            return INT_GETPROCADDRESS_FAIL;
        }

        // 프로세스 핸들로해서 힙 공간 만들고
        LPVOID dllPathAlloc = VirtualAllocEx(hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
        if (NULL == dllPathAlloc)
        {
            printf("Virtual Alloc Failure %d \n", GetLastError());
            return INT_VIRTUALALLOC_FAIL;
        }
        else
        {
            // 메모리 공간 할당에 성공하면
            // 해당 메모리 공간에 문자열 정보 써준다음
            int nLenDLL = strlen(pDllPath);
            DWORD oldProtect = 0;

            VirtualProtectEx(hProcess, (LPVOID)dllPathAlloc, MAX_PATH, PAGE_EXECUTE_READWRITE, &oldProtect);
            if (!WriteProcessMemory(hProcess, dllPathAlloc, pDllPath, nLenDLL, NULL))
            {
                printf("WriteProcessMemory Failure %d \n", GetLastError());

                return INT_WRITEPROCESSMEMORY_FAIL;
            }
            VirtualProtectEx(hProcess, (LPVOID)dllPathAlloc, MAX_PATH, oldProtect, NULL); //restore the original protection when you're done

            HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpfnLoadLibrary, dllPathAlloc, NULL, NULL);
            if (hThread == NULL)
            {

                printf("CreateRemoteThread Failure %d \n", GetLastError());
                return INT_CREATEREMOTETHREAD_FAIL;
            }
        }
    }
    else
    {
        ret = INT_OPENPROCESS_FAIL;
    }

    return ret;
}

