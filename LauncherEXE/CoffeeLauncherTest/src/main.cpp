#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")


#include <windows.h>
#include <iostream>



void MyCreateProcess()
{
	STARTUPINFO si = { sizeof(si) };

	PROCESS_INFORMATION pi;

	TCHAR szCommandLine[] = TEXT("NOTEPAD");
	CreateProcess(NULL, szCommandLine, NULL, NULL,
		FALSE, 0, NULL, NULL, &si, &pi);
}

int main()
{
//	POST();
	
	
	MyCreateProcess();
	OutputDebugString(L"aa");
	std::cout << "sadkjnsadksadsadasdkjn" << std::endl;

	while (true)
	{

	}

	return 0;
}