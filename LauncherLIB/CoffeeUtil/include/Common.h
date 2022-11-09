#pragma once
#include <Windows.h>

#ifdef COFFEEUTIL_EXPORTS    
#define COFFEEUTIL_API __declspec(dllexport)
#else
#define COFFEEUTIL_API __declspec(dllimport)
#endif


