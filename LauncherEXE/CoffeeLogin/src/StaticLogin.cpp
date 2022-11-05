#include <pch.h>
#include "StaticLogin.h"


typedef struct {
	char UserId[32];
	char UserPw[32];
} UserA;


typedef struct {
	wchar_t UserId[32];
	wchar_t UserPw[32];
} UserW;

static UserW users[] = {
	{L"hello", L"world"},
	{L"admin", L"password"},
};

BOOL CStaticLogin::Login(const wchar_t* userId, const wchar_t* userPw)
{
	int nLenUser = sizeof(users) / sizeof(UserW);
	for (int i = 0; i < nLenUser; ++i)
	{
		const UserW user = users[i];
		if (lstrcmpW(userId, user.UserId) == 0 && lstrcmpW(userPw, user.UserPw) == 0)
		{
			return true;
		}
	}

	return false;
}
