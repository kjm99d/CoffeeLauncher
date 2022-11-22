#include "pch.h"
#include "HTTPLogin.h"



CHttpLogin::CHttpLogin(const char * url)
{
	m_url = url;
}

CHttpLogin::~CHttpLogin()
{
}

BOOL CHttpLogin::Login(const wchar_t* userId, const wchar_t* userPw)
{
	m_client.Open(RequestMethod::kPOST, m_url.c_str());
	
	
	wchar_t szPayload[4096] = {0,};
	swprintf_s(szPayload, 4096, L"username=%s&password=%s", userId, userPw);
	
	m_client.Send(szPayload);
	PBYTE res = NULL;
	DWORD sz = 0;
	
	while (m_client.GetBuffer(res, sz))
	{
		WCHAR szMsg[4096] = { 0, };
		MultiByteToWideChar(CP_UTF8, 0, (LPCCH)res, sz, szMsg, 4096);
		MessageBox(NULL, szMsg, NULL, NULL);
	}

	return 0;
}
