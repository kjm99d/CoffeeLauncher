#pragma once
#include <Windows.h>

class ILogin {

public:
	virtual BOOL Login(const wchar_t* userId, const wchar_t* userPw ) = 0;
};
