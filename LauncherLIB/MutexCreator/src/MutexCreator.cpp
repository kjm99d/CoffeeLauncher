#include "MutexCreator.h"

CMutexCreator::CMutexCreator(const char* id)
{
	OutputDebugString(L"CMutexCreator Init");

	m_hMutex = ::CreateMutexA(nullptr, TRUE, id);
	m_GetLastError();
}

CMutexCreator::CMutexCreator(const wchar_t* id)
{
	OutputDebugString(L"CMutexCreator Init");

	m_hMutex = ::CreateMutexW(nullptr, TRUE, id);
	m_GetLastError();
}

CMutexCreator::~CMutexCreator()
{

	OutputDebugString(L"CMutexCreator Close");

	if (m_hMutex) {
		::CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}

}

BOOL CMutexCreator::isAlreadyExists()
{
	return (m_Err == ERROR_ALREADY_EXISTS);
}

void CMutexCreator::m_GetLastError()
{
	m_Err = ::GetLastError();
}
