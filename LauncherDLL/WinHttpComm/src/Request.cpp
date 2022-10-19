#include "Request.h"

#include <iostream>
#include <Windows.h>
#include <Winhttp.h>
#pragma comment (lib, "winhttp.lib")

// ======================================================================= //
static CRequest& inst = CRequest::GetInst();
// ======================================================================= //

int POST()
{
	inst.SetMethod(kGET);
	inst.SetURL(L"https://api.ip.pe.kr/");
	inst.Request();

	return 0;
}

int GET()
{
	inst;
	return 0;

}

// ======================================================================= //
CRequest::CRequest()
{
	OutputDebugString(L"CRequest Init()");
}

CRequest::~CRequest()
{
	OutputDebugString(L"CRequest destroy()");

}

CRequest& CRequest::GetInst()
{
	static CRequest inst;
	return inst;
}

void CRequest::Request()
{
	switch (m_method)
	{
	case RequestMethod::kGET:
		GET();
		break;

	case RequestMethod::kPOST:
		break;

	default:
		break;
	}
}

void CRequest::SetMethod(RequestMethod method)
{
	m_method = method;
}

void CRequest::SetURL(const TCHAR* url)
{
	m_url = url;
}

bool CRequest::POST()
{
	return false;
}

bool CRequest::GET()
{
	HINTERNET      hSession, hConnect, hRequest;
	URL_COMPONENTS urlComponents;
	WCHAR          szHostName[256], szUrlPath[2048];
	WCHAR          szUrl[] = L"https://api.ip.pe.kr/";
	DWORD          dwSize;
	DWORD          dwStatusCode;
	BYTE           buffer[4096];
	memset(buffer, 0x00, 4096);

	hSession = WinHttpOpen(L"sample", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession == NULL)
		return -1;

	ZeroMemory(&urlComponents, sizeof(URL_COMPONENTS));
	urlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	urlComponents.lpszHostName = szHostName;
	urlComponents.dwHostNameLength = sizeof(szHostName) / sizeof(WCHAR);
	urlComponents.lpszUrlPath = szUrlPath;
	urlComponents.dwUrlPathLength = sizeof(szUrlPath) / sizeof(WCHAR);

	if (!WinHttpCrackUrl(szUrl, lstrlenW(szUrl), 0, &urlComponents)) {
		WinHttpCloseHandle(hSession);
		return -2;
	}

	hConnect = WinHttpConnect(hSession, szHostName, INTERNET_DEFAULT_PORT, 0);
	if (hConnect == NULL) {
		WinHttpCloseHandle(hSession);
		return -3;
	}

	hRequest = WinHttpOpenRequest(hConnect, L"GET", szUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (hRequest == NULL) {
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return -4;
	}

	if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return -5;
	}

	WinHttpReceiveResponse(hRequest, NULL);

	dwSize = sizeof(DWORD);
	WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &dwStatusCode, &dwSize, WINHTTP_NO_HEADER_INDEX);
	if (dwStatusCode == HTTP_STATUS_OK)
	{
		WinHttpReadData(hRequest, buffer, sizeof(buffer), NULL);

		std::cout << "성공 Body" << buffer << std::endl;
	}
	else {
		TCHAR szBuf[256];
		wsprintf(szBuf, TEXT("Status Code %d"), dwStatusCode);
		std::wcout << "실패" << szBuf << std::endl;
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);

	return 0;
}
// ======================================================================= //
