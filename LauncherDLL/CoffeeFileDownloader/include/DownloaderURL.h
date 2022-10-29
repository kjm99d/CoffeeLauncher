#pragma once
#include "WinHttpComm/include/Request.h"

#ifdef COFFEEFILEDOWNLOADER_EXPORTS
#define DOWNLOADER_EXPORT __declspec(dllexport)
#else
#define DOWNLOADER_EXPORT __declspec(dllimport)
#endif


class DOWNLOADER_EXPORT CURLDownload {
public:
	CURLDownload();
	CURLDownload(const char* url);
	~CURLDownload();

public:
	BOOL Write(const char * path);
	BOOL DownloadMemory();


private:
	const char* m_url;

private:
	CRequest* m_request;

};
