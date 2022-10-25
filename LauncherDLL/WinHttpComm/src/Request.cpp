#include "Request.h"


#pragma comment (lib, "winhttp.lib")

// ======================================================================= //
CRequest::CRequest() : hSession(NULL)
{
	OutputDebugString(L"CRequest Init()");
}

CRequest::~CRequest()
{
	OutputDebugString(L"CRequest destroy()");

}

int CRequest::Request()
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
		hSession = WinHttpOpen(L"sample", 
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
	

	const TCHAR* wcsUrl = m_url;
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

	const TCHAR* wcsMethod = StrRequestMethodW();
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
		const TCHAR* key = header.first;
		const TCHAR* value = header.second;

		TCHAR szHeader[2048] = { 0, };
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

void CRequest::SetMethod(const RequestMethod method)
{
	m_method = method;
}

void CRequest::SetHeader(const TCHAR* key, const TCHAR* value)
{
	m_headers.push_back({ key, value });
}

void CRequest::SetHeader(request_header headers)
{
	m_headers = headers;
}

void CRequest::SetPayload(const TCHAR* payload)
{
}

void CRequest::SetURL(const TCHAR* url)
{
	m_url = url;
}

void CRequest::SetQueryString(const TCHAR* query)
{
}

const TCHAR* CRequest::StrRequestMethodW()
{
	const WCHAR* wcsGet		= L"GET";
	const WCHAR* wcsPost	= L"POST";
	const WCHAR* wcsDelete	= L"DELETE";
	const WCHAR* wcsPut		= L"PUT";
	const WCHAR* wcsPatch	= L"wcsPatch";

	const WCHAR* strMethod;

	switch (m_method)
	{
	case RequestMethod::kGET:		strMethod = wcsGet;		break;
	case RequestMethod::kPOST:		strMethod = wcsPost;	break;
	case RequestMethod::kDELETE:	strMethod = wcsDelete;	break;
	case RequestMethod::kPUT:		strMethod = wcsPut;		break;
	case RequestMethod::kPATCH:		strMethod = wcsPatch;	break;
		
	default:
		strMethod = L"Error";
		OutputDebugString(L"Error: Request Method check !");
		break;
	}

	return strMethod;

}
// ======================================================================= //
