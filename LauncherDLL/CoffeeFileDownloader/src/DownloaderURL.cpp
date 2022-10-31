#include <Windows.h>
#include <stringapiset.h>
#include "DownloaderURL.h"
#pragma comment(lib, "WinHttpComm.lib")


CURLDownload::CURLDownload() : m_request(new CRequest()), m_url(NULL)
{
	OutputDebugString(L"A");
}

CURLDownload::CURLDownload(const char* url)
{
	m_request = new CRequest();
	m_url = url;

	//CURLDownload();
	OutputDebugString(L"B");
	WCHAR szUrl[2048] = { 0, };

	MultiByteToWideChar(CP_ACP, 0, m_url, -1, szUrl, sizeof(szUrl));

	m_request->SetURL(szUrl);

}

CURLDownload::~CURLDownload()
{
	delete m_request;
}

BOOL CURLDownload::Write(const char* path)
{
	BOOL ret = false;

	FILE* fd = NULL;
	errno_t errCode = fopen_s(&fd, path, "wb");
	switch (errCode)
	{
	default:
		break;
	}
	//const std::string buf = m_request->GetResponseBody();
	//fwrite(buf.c_str(), 1, buf.size(), fd);
	//fclose(fd);
	fd = NULL;

	return ret;
}

BOOL CURLDownload::DownloadMemory()
{
	BOOL ret = false;

	m_request->SetMethod(RequestMethod::kGET);
	m_request->Request();

	return ret;
}
