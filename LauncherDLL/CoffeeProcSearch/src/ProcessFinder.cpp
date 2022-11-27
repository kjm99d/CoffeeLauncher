#include "ProcessFinder.h"
#include "tlhelp32.h"


#define FIND_PROCESS_MODE_PID           0x01
#define FIND_PROCESS_MODE_PROCESSNAME   0x02
#define FIND_PROCESS_MODE_PID_PROCESSNAME FIND_PROCESS_MODE_PID | FIND_PROCESS_MODE_PROCESSNAME


typedef struct _FIND_PROCESS_INFO{
    int     nMode;
    DWORD   dwPid;
    char    szProcessName[MAX_PATH];
} FIND_PROCESS_INFO;

BOOL FindProcess(FIND_PROCESS_INFO * info);


BOOL IsX64Process(DWORD dwPID)
{
    BOOL bIsWow64 = 0;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPID);
    BOOL ret = 0;
    if (hProcess) {
        ret = IsWow64Process(hProcess, &bIsWow64);
        CloseHandle(hProcess);
    }

    
    return 0 == bIsWow64 && 1 == ret;
}

BOOL GetProcessIdFromName(const char* pProcessName, std::vector<DWORD>* pids)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    BOOL bStatus = false;
    pids->clear();

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        //printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
        return FALSE;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return FALSE;
    }

    do
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pe32.th32ProcessID);
        if (hProcess)
        {
            const WCHAR* szFileName = pe32.szExeFile;
            const DWORD dwPid = pe32.th32ProcessID;

            char szBuffer[MAX_PATH] = { 0, };
            WideCharToMultiByte(CP_UTF8, 0, szFileName, lstrlenW(szFileName), szBuffer, MAX_PATH, NULL, NULL);

            if (0 == strcmp("LoveBeat.exe", szBuffer)) {
                pids->push_back(dwPid);
            }

            CloseHandle(hProcess);
        }


    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return pids->empty() > 0;
}

BOOL FindProcessFromID(DWORD PID)
{
    FIND_PROCESS_INFO info;
    memset(&info, 0x00, sizeof(FIND_PROCESS_INFO));
    info.nMode = FIND_PROCESS_MODE_PID;
    info.dwPid = PID;
    return FindProcess(&info);
}


BOOL FindProcessByName(char* strProcessName)
{
    FIND_PROCESS_INFO info;
    memset(&info, 0x00, sizeof(FIND_PROCESS_INFO));
    info.nMode = FIND_PROCESS_MODE_PROCESSNAME;
    memcpy_s(info.szProcessName, MAX_PATH, strProcessName, strlen(strProcessName));
    return FindProcess(&info);
}




BOOL FindProcess(FIND_PROCESS_INFO * info)
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    BOOL bStatus = false;;

    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        //printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
        return FALSE;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process,
    // and exit if unsuccessful
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap); 
        return FALSE;
    }

    do
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pe32.th32ProcessID);
        if (hProcess)
        {
            const WCHAR* szFileName = pe32.szExeFile;
            const DWORD dwPid = pe32.th32ProcessID;

            char szBuffer[MAX_PATH] = { 0, };
            WideCharToMultiByte(CP_UTF8, 0, szFileName, lstrlenW(szFileName), szBuffer, MAX_PATH, NULL, NULL);
            
           

            if (info->nMode & FIND_PROCESS_MODE_PID)
            {
                bStatus = (dwPid == info->dwPid);
            }

            if (info->nMode & FIND_PROCESS_MODE_PROCESSNAME)
            {
                bStatus = (0 == strcmp(szBuffer, info->szProcessName));

            }

            CloseHandle(hProcess);

            if (bStatus)
            {
                break;
            }
        }


    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    
    return bStatus;
}
