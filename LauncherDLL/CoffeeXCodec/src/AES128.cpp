#include "AES128.h"
#include "aes128/aes.h"

#define AES_KEY "HELLO WORLD"

CAES128::CAES128()
{
	buffer = NULL;
	dest = NULL;
	m_nLenBuffer = m_nLenDest = 0;
}

CAES128::~CAES128()
{
	free(buffer);
	buffer = nullptr;
	m_nLenBuffer = 0;
}

bool CAES128::GetEncryptBuffer(const unsigned char*& pDest, int& nLenDest)
{
	bool bSuccess = CheckRule();
	if (bSuccess)
	{
		if (dest) {
			dest = (unsigned char *)malloc(m_nLenBuffer * sizeof(unsigned char));
		}

		AES_ECB_Encrypt(
            static_cast<const unsigned char *>(buffer), static_cast<const unsigned char *>(AES_KEY), 
            dest, m_nLenBuffer);

		pDest = dest;
		nLenDest = m_nLenDest;
	}

	bool bRet = bSuccess;
	return bRet;
}

bool CAES128::GetDecryptBuffer(const unsigned char*& pDest, int& nLenDest)
{
	bool bSuccess = CheckRule();
	if (bSuccess)
	{

	}

	bool bRet = bSuccess;
	return bRet;
}

bool CAES128::SetSource(unsigned char* pSource, int nLenSource)
{
	try
	{
		const int nLenBuffer = sizeof(unsigned char) * nLenSource;
		buffer = (unsigned char*)malloc(nLenBuffer);
		if (buffer) 
		{
			//memset(buffer, 0x00, nLenBuffer);
			memcpy_s(buffer, nLenBuffer, pSource, nLenSource);
		}
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool CAES128::CheckRule()
{
	/*
	* 16의 배수 체크
	*/
	return false;
}
