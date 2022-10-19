#include <Windows.h>


int main()
{
	typedef int (*fp_WinHttpPost)();
	HMODULE hMod = LoadLibrary(L"WinHttpComm.dll");
	LPCSTR my_str = "POST";
	fp_WinHttpPost req = (fp_WinHttpPost)GetProcAddress(hMod, my_str);
	req();
	

	return 0;
}