#include "DLLInjector.h"

int Inject(const DWORD dwPid, const char* pDllPath)
{
    int ret = INT_INJECTION_SUCCESS;

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPid);
    if (hProcess)
    {

        // DLL 로딩 함수 구하고 
        HMODULE hKernel32 = LoadLibrary(L"Kernel32.dll");
        if (!hKernel32)
        {
            return INT_LOADLIBRARY_FAIL;
        }

        FARPROC lpfnLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");

        // 프로세스 핸들로해서 힙 공간 만들고
        LPVOID dllPathAlloc = VirtualAllocEx(hProcess, NULL, sizeof(WCHAR) * MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
        if (dllPathAlloc == NULL)
        {
            return INT_LOADLIBRARY_FAIL;
        }
        else
        {
            // 메모리 공간 할당에 성공하면
            // 해당 메모리 공간에 문자열 정보 써준다음
            int nLenDLL = strlen(pDllPath);
            if (!WriteProcessMemory(hProcess, dllPathAlloc, pDllPath, nLenDLL, NULL))
            {
                return INT_WRITEPROCESSMEMORY_FAIL;
            }

            HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpfnLoadLibrary, dllPathAlloc, NULL, NULL);
            if (hThread == NULL)
            {
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

