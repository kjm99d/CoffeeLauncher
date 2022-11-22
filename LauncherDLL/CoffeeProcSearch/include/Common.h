#pragma once

#include <Windows.h>

#ifdef COFFEEPROCSEARCH_EXPORTS
    #define COFFEEPROCSEARCH_API __declspec(dllexport)
#else
    #define COFFEEPROCSEARCH_API __declspec(dllimport)
#endif



