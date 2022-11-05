#include <Windows.h>
#include <stringapiset.h>
#include "DownloaderURL.h"
#pragma comment(lib, "WinHttpComm.lib")


CURLDownload::CURLDownload()
{
	m_request = new CRequest();
}

CURLDownload::~CURLDownload()
{
	if (m_request) {
		delete m_request;
		m_request = nullptr;
	}
}

BOOL CURLDownload::Download(const char* url, const char* path)
{
	wchar_t wszUrl[2048] = { 0, };
	MultiByteToWideChar(CP_ACP, 0, url, -1, wszUrl, 2048);

	m_request->Open(RequestMethod::kGET, wszUrl);
	m_request->Send();


	// 정상응답값이 아닌 경우
	if (m_request->GetStatusCode() != 200) 
	{
		return false;
	}
	
	FILE* fd = NULL;
	fopen_s(&fd, path, "wb");



	bool status = true;
	while (status)
	{
		PBYTE buffer = nullptr;
		DWORD dwBufferSize = 0;
		status = m_request->GetBuffer(buffer, dwBufferSize);

		if (buffer == nullptr)
		{
			OutputDebugString(L"Response Buffer Size = 0");
		}

		fwrite(buffer, 1, dwBufferSize, fd);
	}

	fclose(fd);
	fd = NULL;


}

BOOL CURLDownload::Download(const wchar_t* url, const wchar_t* path)
{
	char szUrl[2048] = { 0, };
	char szPath[2048] = { 0, };

	WideCharToMultiByte(CP_ACP, 0, url, -1, szUrl, sizeof(szUrl), 0, 0);
	WideCharToMultiByte(CP_ACP, 0, url, -1, szPath, sizeof(szPath), 0, 0);


	return Download(szUrl, szPath);
}

BOOL CURLDownload::DownloadMemory()
{
	BOOL ret = false;
	return ret;
}
