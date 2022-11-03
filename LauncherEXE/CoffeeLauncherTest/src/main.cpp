#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")


#include <CoffeeFileDownloader/include/DownloaderURL.h>
#pragma comment(lib, "CoffeeFileDownloader.lib")



#include <windows.h>
#include <iostream>


#include <vector>
using namespace std;

namespace EXAMPLE {
	void WinHttpRequest()
	{
		CRequest client;

		client.Open(RequestMethod::kGET, L"http://127.0.0.1:5000/form");
		client.SetHeader(L"user-agent", L"Hello");
		client.Send();

		DWORD dwStatusCode = client.GetStatusCode();

		PBYTE responseBuffer = NULL;
		DWORD dwReadDataSize = 0;

		if (dwStatusCode != 200)
		{
			return void();
		}

		while (client.GetBuffer(responseBuffer, dwReadDataSize))
		{
			printf("%s", responseBuffer);
		}
	};


	void FileDownload()
	{
		CURLDownload loader;
		loader.Download("http://10.20.10.73/635f78d1b22de.jpg", "D:\\test.jpg");
	}
}

void ExampleWinHttp()
{


	return void();
}

int main()
{
	/*
	CURLDownload * downloader = new CURLDownload("http://192.168.0.4:8085/windbg.exe");
	downloader->DownloadMemory();
	downloader->Write("D:\\test.exe");
	*/

	//ExampleWinHttp();
	
	EXAMPLE::FileDownload();

}