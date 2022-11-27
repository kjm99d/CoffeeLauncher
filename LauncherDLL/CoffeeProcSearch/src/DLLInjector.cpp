#include "DLLInjector.h"
#include <stdio.h>

int Inject(const DWORD dwPid, const char* pDllPath)
{
    int ret = INT_INJECTION_SUCCESS;

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

