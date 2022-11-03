#pragma once
#include "ILogin.h"

class CHttpLogin : public ILogin
{
public:
	BOOL Login(const wchar_t* userId, const wchar_t* userPw);
};
