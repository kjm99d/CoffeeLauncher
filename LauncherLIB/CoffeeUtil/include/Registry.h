#pragma once
#include "Common.h"

/**
 * @brief 레지스트리의 값을 조회하는 함수.
 * 
 * @param RootKey - 루트키 값
 * @param csSubKey - 서브키 값
 * @param szValue - 읽은 값을 전달받을 문자열 버퍼
 * @param dwSize - 읽은 버퍼의 크기
 * 
 * @return BOOL 성공 - 1, 실패 -  0
 */
COFFEEUTIL_API BOOL RegKeyRead(HKEY RootKey, const char* csSubKey, const char* csValue, char* szValue, DWORD* dwSize);




