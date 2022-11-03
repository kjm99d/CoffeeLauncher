#pragma once
#include "ILogin.h"

class CStaticLogin : public ILogin
{
public:
	BOOL Login(const wchar_t* userId, const wchar_t* userPw);
};
