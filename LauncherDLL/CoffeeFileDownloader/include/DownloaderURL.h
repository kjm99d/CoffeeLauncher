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
	~CURLDownload();

public:
	BOOL Download(const char * url, const char * path);
	BOOL Download(const wchar_t * url, const wchar_t * path);
	BOOL DownloadMemory();

private:
	CRequest* m_request;

};
