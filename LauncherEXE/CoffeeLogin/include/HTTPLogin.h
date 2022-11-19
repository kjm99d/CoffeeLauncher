#pragma once
#include "ILogin.h"
#include "WinHttpComm/include/Request.h"

#pragma comment(lib, "WinHttpComm.lib")

class CHttpLogin : public ILogin
{
public:
    CHttpLogin(const char * url);
    ~CHttpLogin();

public:
	BOOL Login(const wchar_t* userId, const wchar_t* userPw);


private:
    std::string m_url;
    CRequest m_client;

};
