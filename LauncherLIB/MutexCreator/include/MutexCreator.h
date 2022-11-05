#pragma once

#ifdef MUTEXCREATOR_EXPORTS
	#define MUTEXCREATOR_EXPORT __declspec(dllexport) 
#else
	#define MUTEXCREATOR_EXPORT __declspec(dllimport) 
#endif

#include <Windows.h>

class MUTEXCREATOR_EXPORT CMutexCreator
{
private:
	HANDLE m_hMutex;
	DWORD m_Err;
public:
	CMutexCreator(const char* id);
	CMutexCreator(const wchar_t* id);
	~CMutexCreator();


	BOOL isAlreadyExists();
	
private:
	void m_GetLastError();
};
