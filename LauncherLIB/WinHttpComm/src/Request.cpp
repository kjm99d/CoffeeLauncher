#include "Request.h"
#include <atlstr.h>


#pragma comment (lib, "winhttp.lib")

// ======================================================================= //
CRequest::CRequest(const wchar_t* url)
{
	OutputDebugString(L"CRequest Init()");

	hSession = NULL;


	// 멤버 변수 URL을 설정하고
	SetURL(url);
	// 세션을 할당받고
	//Open();
	// 컴포넌트 파싱
	//SetComponent();

	const wchar_t* wcsUrl = m_url;
	if (!WinHttpCrackUrl(wcsUrl, lstrlenW(wcsUrl), 0, &m_urlComponents)) {
		WinHttpCloseHandle(hSession);
		//return -2;
	}

	// 커넥션 열고
	const INTERNET_PORT nPort = m_urlComponents.nPort; /* WORD */
	m_hConnect = WinHttpConnect(hSession, m_szHostName, nPort, 0);
	if (m_hConnect == NULL) {
		WinHttpCloseHandle(hSession);
		//return -3;
	}
	
}

CRequest::CRequest(const RequestMethod method, wchar_t* url)
{
	
}

CRequest::~CRequest()
{
	OutputDebugString(L"CRequest destroy()");
	Close();
}

RequestError CRequest::GetLastError()
{
	return RequestError();
}

void CRequest::Open(RequestMethod method, const wchar_t* url)
{	
	// Create Session
	CreateSession();
	// SetComponent
	SetComponent(url);
}

void CRequest::Send(const wchar_t* form)
{
	
}

int CRequest::Request()
{
	
	//m_responseBody.clear();

	DWORD          dwSize;


	const wchar_t* wcsMethod = StrRequestMethodW();
	m_hRequest = WinHttpOpenRequest(
		m_hConnect, wcsMethod, m_szUrlPath, 
		NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	if (m_hRequest == NULL) {
		WinHttpCloseHandle(m_hConnect);
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

		WinHttpAddRequestHeaders(m_hRequest, szHeader, -1L, WINHTTP_ADDREQ_FLAG_ADD);

	}
	

	if (!WinHttpSendRequest(m_hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
		DWORD dwError = GetLastError();
		WinHttpCloseHandle(m_hRequest);
		WinHttpCloseHandle(m_hConnect);
		WinHttpCloseHandle(hSession);
		return -5;
	}

	WinHttpReceiveResponse(m_hRequest, NULL);

	dwSize = sizeof(DWORD);
	WinHttpQueryHeaders(m_hRequest, 
		WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, 
		WINHTTP_HEADER_NAME_BY_INDEX, 
		&m_dwStatusCode, 
		&dwSize, WINHTTP_NO_HEADER_INDEX);

	
	
	return 0;


}

void CRequest::SetMethod(const RequestMethod method)
{
	m_method = method;
}

void CRequest::SetHeader(const wchar_t* key, const wchar_t* value)
{
	m_headers.push_back({ key, value });
}

void CRequest::SetHeader(request_header headers)
{
	m_headers = headers;
}

void CRequest::SetPayload(const wchar_t* payload)
{
}

void CRequest::SetURL(const wchar_t* url)
{
	// 메모리 초기화
	RtlZeroMemory(m_url, sizeof(m_url) / sizeof(WCHAR));
	// 문자열 복사
	swprintf_s(m_url, 4096, L"%s", url);

	//OutputDebugString(m_url);
}


const wchar_t* CRequest::StrRequestMethodW()
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

void CRequest::CreateSession(const wchar_t* session = NULL)
{
	/*
	* 현재 hSession 값이 NULL일 경우에만, 새로운 세션을 생성 시키고,
	* 만약 NULL이 아닌 경우 기존 세션을 유지한채로 Request Logic을 수행한다.
	*/
	if (hSession == NULL) {
		hSession = WinHttpOpen(session,
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);
	}


}
void CRequest::SetComponent(const wchar_t * url)
{

	ZeroMemory(&m_urlComponents, sizeof(URL_COMPONENTS));
	m_urlComponents.dwStructSize = sizeof(URL_COMPONENTS);
	m_urlComponents.lpszHostName = m_szHostName;
	m_urlComponents.dwHostNameLength = sizeof(m_szHostName) / sizeof(WCHAR);
	m_urlComponents.lpszUrlPath = m_szUrlPath;
	m_urlComponents.dwUrlPathLength = sizeof(m_szUrlPath) / sizeof(WCHAR);


	const wchar_t* wcsUrl = url;
	if (!WinHttpCrackUrl(wcsUrl, lstrlenW(wcsUrl), 0, &m_urlComponents)) {
		WinHttpCloseHandle(hSession);
		//return -2;
	}
}


DWORD CRequest::GetStatusCode()
{
	return m_dwStatusCode;
}

BOOL CRequest::GetBuffer(PBYTE& pbBufferStorage,DWORD& dwReadDataSize)
{
	RtlZeroMemory(m_ResponseBuffer, sizeof(m_ResponseBuffer) / sizeof(WCHAR));
	if (m_dwStatusCode == HTTP_STATUS_OK)
	{

		DWORD dwTempReadDataSize;

#if 0
		do {

			

		} while (dwReadDataSize >= 4096);
#else
		BOOL status = WinHttpReadData(m_hRequest, m_ResponseBuffer, sizeof(m_ResponseBuffer), &dwTempReadDataSize);
		status = (status && dwTempReadDataSize);
		if (status)
		{
			pbBufferStorage = m_ResponseBuffer;
			dwReadDataSize = dwTempReadDataSize;
		}
		else
		{
			pbBufferStorage = NULL;
			dwReadDataSize = 0;
		}
		return status;
		
#endif
	}
	else {
		wchar_t szBuf[256];
		wsprintf(szBuf, TEXT("Status Code %d"), m_dwStatusCode);
		std::wcout << "실패" << szBuf << std::endl;
	}
}
void CRequest::Close()
{
	WinHttpCloseHandle(m_hRequest);
	WinHttpCloseHandle(m_hConnect);
	WinHttpCloseHandle(hSession);
}

// ======================================================================= //

const char* GetRequestErrorString(RequestError err)
{
	const char* ret;
	switch (err)
	{
	//case RequestError::ERROR_NONE: 
	default:
		ret = NULL;
		break;
	}

	return ret;
}
