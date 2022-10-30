#include "RequestFile.h"

CRequestFile::CRequestFile(FILE* fd) : CRequest(L"aa")
{
	m_fd = fd;
}

CRequestFile::~CRequestFile()
{
}

int CRequestFile::Write()
{
	HINTERNET      hConnect, hRequest;
	URL_COMPONENTS urlComponents;
	WCHAR          szHostName[256], szUrlPath[2048];
	DWORD          dwSize;
	DWORD          dwStatusCode;
	BYTE           buffer[4096];
	RtlZeroMemory(buffer, 4096);

	/*
	* 현재 hSession 값이 NULL일 경우에만, 새로운 세션을 생성 시키고,
	* 만약 NULL이 아닌 경우 기존 세션을 유지한채로 Request Logic을 수행한다.
	*/
	if (hSession == NULL) {
		hSession = WinHttpOpen(L"a",
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);
		if (hSession == NULL)
			return -1;
	}

	ZeroMemory(&urlComponents, sizeof(URL_COMPONENTS));
	urlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	urlComponents.lpszHostName = szHostName;
	urlComponents.dwHostNameLength = sizeof(szHostName) / sizeof(WCHAR);
	urlComponents.lpszUrlPath = szUrlPath;
	urlComponents.dwUrlPathLength = sizeof(szUrlPath) / sizeof(WCHAR);


	const wchar_t* wcsUrl = NULL;// = tmp;
	if (!WinHttpCrackUrl(wcsUrl, lstrlenW(wcsUrl), 0, &urlComponents)) {
		WinHttpCloseHandle(hSession);
		return -2;
	}

	const INTERNET_PORT nPort = urlComponents.nPort; /* WORD */
	hConnect = WinHttpConnect(hSession, szHostName, nPort, 0);
	if (hConnect == NULL) {
		WinHttpCloseHandle(hSession);
		return -3;
	}

	const wchar_t* wcsMethod = StrRequestMethodW();
	hRequest = WinHttpOpenRequest(
		hConnect, wcsMethod, szUrlPath,
		NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (hRequest == NULL) {
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		return -4;
	}

	/*
	* Header Iterator
	* 헤더를 순회하면서, 헤더값을 추가해 서버에 요청한다.
	*/
	for (auto& header : m_headers)
	{
		const wchar_t* key = header.first;
		const wchar_t* value = header.second;

		wchar_t szHeader[2048] = { 0, };
		swprintf_s(szHeader, 2048, L"%s: %s", key, value);

		WinHttpAddRequestHeaders(hRequest, szHeader, -1L, WINHTTP_ADDREQ_FLAG_ADD);

	}


	if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
		DWORD dwError = GetLastError();
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

		DWORD dwReadDataSize;

		do {

			WinHttpReadData(hRequest, buffer, sizeof(buffer), &dwReadDataSize);
			fwrite(buffer, 1, dwReadDataSize, m_fd);
			//void* m_ptr = buffer;
			//m_responseBody.append((const char* const)m_ptr, 4096);
			memset(buffer, 0x00, 4096);

		} while (dwReadDataSize >= 4096);

		fclose(m_fd);
		m_fd = NULL;
	}
	else {
		wchar_t szBuf[256];
		wsprintf(szBuf, TEXT("Status Code %d"), dwStatusCode);
		std::wcout << "실패" << szBuf << std::endl;
	}

	WinHttpCloseHandle(hRequest);
	WinHttpCloseHandle(hConnect);
	WinHttpCloseHandle(hSession);

	return 0;


}
