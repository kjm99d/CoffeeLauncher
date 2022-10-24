#pragma once

#ifdef WINHTTPCOMM_EXPORTS
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#else
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#endif

#include <tchar.h>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <Windows.h>
#include <winhttp.h>

/**
 * Single Vector ���·� Key�� Value�� �����ϴ� ����Ʈ
 */
typedef std::vector<std::pair<const TCHAR*, const TCHAR*>> request_header;

typedef enum {
	None,
	kGET,
	kPOST,
	kPUT,
	kDELETE,
	kPATCH,
} RequestMethod;

class WINHTTPCOMM_EXPORT CRequest
{

public:
	CRequest();
	~CRequest();

public:
	// 

	/**
	 * Set[...] ����� �Լ��� ������ �پ��� �Ķ���� �ɼ��� ������� �������� �����͸� ��û�մϴ�.
	 * 
	 * \return �����ڵ�
	 */
	int Request();

	
	/**
	 * ��û�� URL�� �����մϴ�.
	 * 
	 * \param url - ��û URL�� �Է��մϴ�.
	 */
	void SetURL(const TCHAR* url);

	/**
	 * ��û �޼ҵ带 �����մϴ�.
	 * 
	 * \param method - RequestMethod Enum ����
	 */
	void SetMethod(const RequestMethod method);

	/**
	 * ��û����� �����մϴ�.
	 * �ѹ� ���� �� �������� ������ϴ�.
	 * 
	 * \param key - ����� Ű��
	 * \param value - ����� �����
	 */
	void SetHeader(const TCHAR* key, const TCHAR* value);

	/**
	 * std::pair Ÿ�����ε� �迭�� �Է����� �޾� ����� �����մϴ�.
	 * 
	 * \param headers header key�� value�� ������ �迭
	 */
	void SetHeader(request_header headers);


private:
	/**
	 * ���� ������ ��û �޼ҵ带 ������� ���ڿ�ȭ�� ��û �޼ҵ带 �����մϴ�.
	 * 
	 * \return 
	 */
	const TCHAR* StrRequestMethodW();

private:
	request_header m_headers;
	RequestMethod m_method;	// ��û �޼ҵ� Ÿ��
	const TCHAR* m_url;		// ��û URL
	HINTERNET hSession;		// ��û ����

	

};




#if __cplusplus
extern "C" {
#endif

	WINHTTPCOMM_EXPORT int POST();
	WINHTTPCOMM_EXPORT int GET();
	


#if __cplusplus
}
#endif