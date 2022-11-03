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
	 * @brief �ٿ�ε� ���� URL�� ����� ���� ��ġ ������ �Ķ���ͷ� �޾�
	 * @brief ������ �ϵ��ũ�� �������ִ� �Լ�
	 * 
	 * \param url - ������ ����� ���� ���� �ּ�
	 * \param path - �ϵ��ũ�� ����� ���
	 * \return - ���� ������ ��������
	 */
	BOOL Download(const char * url, const char * path);


	/**
	 * Wide Character Ÿ���� ���ڿ��� �޾� �ٿ�ε� ���ִ� �Լ�.
	 * 
	 * \param url - ������ ����� ���� ���� �ּ�
	 * \param path - �ϵ��ũ�� ����� ���
	 * \return - ���� ������ ���� ����
	 */
	BOOL Download(const wchar_t * url, const wchar_t * path);

	/**
	 * @brief �޸𸮿� ������ �������ִ� �Լ�.
	 * @brief ���� ���� ���� ����.
	 * \return 
	 */
	BOOL DownloadMemory();

private:
	CRequest* m_request;

};
