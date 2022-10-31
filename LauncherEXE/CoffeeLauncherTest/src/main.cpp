#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")


#include <CoffeeFileDownloader/include/DownloaderURL.h>
#pragma comment(lib, "CoffeeFileDownloader.lib")



#include <windows.h>
#include <iostream>


#include <vector>
using namespace std;


size_t UTF8ToUnicode(char* UTF8, wchar_t& uc)

{

	size_t tRequiredSize = 0;



	uc = 0x0000;



	// ASCII byte 

	if (0 == (UTF8[0] & 0x80))

	{

		uc = UTF8[0];

		tRequiredSize = 1;

	}

	else // Start byte for 2byte

		if (0xC0 == (UTF8[0] & 0xE0) &&

			0x80 == (UTF8[1] & 0xC0))

		{

			uc += (UTF8[0] & 0x1F) << 6;

			uc += (UTF8[1] & 0x3F) << 0;

			tRequiredSize = 2;

		}

		else // Start byte for 3byte

			if (0xE0 == (UTF8[0] & 0xE0) &&

				0x80 == (UTF8[1] & 0xC0) &&

				0x80 == (UTF8[2] & 0xC0))

			{

				uc += (UTF8[0] & 0x1F) << 12;

				uc += (UTF8[1] & 0x3F) << 6;

				uc += (UTF8[2] & 0x3F) << 0;

				tRequiredSize = 3;

			}

			else

			{

				// Invalid case

				//assert(false);

			}



	return tRequiredSize;

}


BOOL ConvertUnicodeToMultibyte(LPCWSTR unicodeStr, LPSTR multiByteStr, DWORD size)

{

	DWORD minSize;

	minSize = WideCharToMultiByte(CP_OEMCP, NULL, unicodeStr, -1, NULL, 0, NULL, FALSE);

	if (size < minSize)

	{

		return FALSE;

	}



	WideCharToMultiByte(CP_OEMCP, NULL, unicodeStr, -1, multiByteStr, size, NULL, FALSE);

	return TRUE;

}

int utf8ToNormalMultiByteStr(const char* utfstr, char* str)

{

	int size = MultiByteToWideChar(CP_UTF8, 0, utfstr, -1, 0, 0);

	vector<wchar_t>		wbuffer(size);

	size = MultiByteToWideChar(CP_UTF8, 0, utfstr, -1, &wbuffer[0], size);



	int cnt = WideCharToMultiByte(CP_ACP, 0, &wbuffer[0], -1, str, size * 2, NULL, NULL);



	return cnt;

}

void MyCreateProcess()
{
	STARTUPINFO si = { sizeof(si) };

	PROCESS_INFORMATION pi;

	TCHAR szCommandLine[] = TEXT("NOTEPAD");
	CreateProcess(NULL, szCommandLine, NULL, NULL,
		FALSE, 0, NULL, NULL, &si, &pi);
}

void ExampleWinHttp()
{
	CRequest client;

	client.Open(RequestMethod::kGET, L"http://127.0.0.1:5000/form");
	client.SetHeader(L"user-agent", L"Hello");
	client.Send();

	//client.Request();

	DWORD dwStatusCode = client.GetStatusCode();

	PBYTE responseBuffer = NULL;
	DWORD dwReadDataSize = 0; 

	while (client.GetBuffer(responseBuffer, dwReadDataSize))
	{


		

		
	}

	return void();
}

int main()
{
	/*
	CURLDownload * downloader = new CURLDownload("http://192.168.0.4:8085/windbg.exe");
	downloader->DownloadMemory();
	downloader->Write("D:\\test.exe");
	*/

	ExampleWinHttp();


}