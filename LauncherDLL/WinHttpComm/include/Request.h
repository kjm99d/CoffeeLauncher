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
 * Single Vector 형태로 Key와 Value를 저장하는 리스트
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
	 * Set[...] 기반의 함수로 설정된 다양한 파라미터 옵션을 기반으로 웹서버에 데이터를 요청합니다.
	 * 
	 * \return 에러코드
	 */
	int Request();

	
	/**
	 * 요청할 URL을 설정합니다.
	 * 
	 * \param url - 요청 URL을 입력합니다.
	 */
	void SetURL(const TCHAR* url);

	/**
	 * 요청 메소드를 설정합니다.
	 * 
	 * \param method - RequestMethod Enum 참조
	 */
	void SetMethod(const RequestMethod method);

	/**
	 * 요청헤더를 설정합니다.
	 * 한번 적용 시 기존값은 사라집니다.
	 * 
	 * \param key - 헤더의 키값
	 * \param value - 헤더의 밸류값
	 */
	void SetHeader(const TCHAR* key, const TCHAR* value);

	/**
	 * std::pair 타입으로된 배열을 입력으로 받아 헤더를 구성합니다.
	 * 
	 * \param headers header key와 value로 구성된 배열
	 */
	void SetHeader(request_header headers);


private:
	/**
	 * 현재 설정된 요청 메소드를 기반으로 문자열화된 요청 메소드를 전달합니다.
	 * 
	 * \return 
	 */
	const TCHAR* StrRequestMethodW();

private:
	request_header m_headers;
	RequestMethod m_method;	// 요청 메소드 타입
	const TCHAR* m_url;		// 요청 URL
	HINTERNET hSession;		// 요청 세션

	

};




#if __cplusplus
extern "C" {
#endif

	WINHTTPCOMM_EXPORT int POST();
	WINHTTPCOMM_EXPORT int GET();
	


#if __cplusplus
}
#endif