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
	/**
	 * @brief 다운로드 받을 URL과 저장될 파일 위치 정보를 파라미터로 받아
	 * @brief 파일을 하드디스크에 저장해주는 함수
	 * 
	 * \param url - 파일이 저장된 파일 서버 주소
	 * \param path - 하드디스크의 저장될 경로
	 * \return - 파일 저장의 성공여부
	 */
	BOOL Download(const char * url, const char * path);


	/**
	 * Wide Character 타입의 문자열을 받아 다운로드 해주는 함수.
	 * 
	 * \param url - 파일이 저장된 파일 서버 주소
	 * \param path - 하드디스크의 저장될 경로
	 * \return - 파일 저장의 성공 여부
	 */
	BOOL Download(const wchar_t * url, const wchar_t * path);

	/**
	 * @brief 메모리에 파일을 저장해주는 함수.
	 * @brief 현재 구현 되지 않음.
	 * \return 
	 */
	BOOL DownloadMemory();

private:
	CRequest* m_request;

};
