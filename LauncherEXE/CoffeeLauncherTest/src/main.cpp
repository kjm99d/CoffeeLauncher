#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")


#include <CoffeeFileDownloader/include/DownloaderURL.h>
#pragma comment(lib, "CoffeeFileDownloader.lib")



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
	/*
	CURLDownload * downloader = new CURLDownload("http://192.168.0.4:8085/windbg.exe");
	downloader->DownloadMemory();
	downloader->Write("D:\\test.exe");
	*/

	CRequest client(L"http://192.168.0.4:8085/windbg.exe");
	client.SetMethod(RequestMethod::kGET);
	request_header hdrs = { {L"user-agent", L"Hello"} };
	client.SetHeader(hdrs);


	client.Request();

	DWORD dwStatusCode = client.GetStatusCode();
	
	PBYTE responseBuffer = NULL;
	DWORD dwReadDataSize = 0;

	while (client.GetBuffer(responseBuffer, dwReadDataSize))
	{
		std::string tmp;
		//tmp.append(PBYTE(), (size_t)0);
		tmp.append(
			(const char *)responseBuffer, 
			static_cast<size_t>(dwReadDataSize)
		);
		std::cout << tmp << std::endl;
	}


}