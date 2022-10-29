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
#include <string>

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
	 * \brief Set[...] 기반의 함수로 설정된 다양한 파라미터 옵션을 기반으로 웹서버에 데이터를 요청합니다.
	 * 
	 * \return 에러코드
	 */
	int Request();

	
	/**
	 * \brief 요청할 URL을 설정합니다.
	 * 
	 * \param url - 요청 URL을 입력합니다.
	 */
	void SetURL(const TCHAR* url);

	/**
	 * \brief 요청 메소드를 설정합니다.
	 * 
	 * \param method - RequestMethod Enum 참조
	 */
	void SetMethod(const RequestMethod method);

	/**
	 * \brief 요청헤더를 설정합니다. 
	 * 
	 * \param key - 헤더의 키값
	 * \param value - 헤더의 밸류값
	 */
	void SetHeader(const TCHAR* key, const TCHAR* value);

	/**
	 * \brief std::pair 타입으로된 배열을 입력으로 받아 헤더를 구성합니다.
	 * 
	 * \param headers header key와 value로 구성된 배열
	 */
	void SetHeader(request_header headers);

	/**
	 * UserAgent 헤더를 설정한다.
	 * 
	 * \param value - 설정될 UserAgent
	 */
	void SetUserAgent(const TCHAR* value);


	/**
	 * \brief 요청 파라미터에 들어갈 페이로드를 설정한다.
	 * \brief 만약 GET 방식의 요청인 경우 페이로드를 설정하지 않는다.
	 * 
	 * \param payload - 페이로드
	 */
	void SetPayload(const TCHAR* payload);

	
	/**
	 * \brief 요청에 필요한 QueryString을 지정한다.
	 * \brief 해당 메소드에서 처리되는 문자열 포맷
	 * \brief Example : "?a=ab&b=ac"
	 * \brief 위와 같이 처리한다.
	 * 
	 * 
	 * \param query - 설명에 Example 참고
	 */
	void SetQueryString(const TCHAR* query);

	/**
	 * \brief Request() 호출 이후에, 서버로 부터 받은 ResponseBody 내용을 가져오는 함수.
	 * 
	 * \return 
	 */
	std::string GetResponseBody();


private:
	/**
	 * 현재 설정된 요청 메소드를 기반으로 문자열화된 요청 메소드를 전달합니다.
	 * 
	 * \return 
	 */
	const TCHAR* StrRequestMethodW();
	
	/**
	 * SetURL로 인해 지정된 파라미터가 있을 경우, 처리한다.
	 * 
	 * \return 
	 */
	void ReplaceQueryString(const TCHAR* buffer, size_t buffer_size);

private:
	request_header m_headers;
	RequestMethod m_method;		// 요청 메소드 타입
	TCHAR m_url[4096];			// 요청 URL
	const TCHAR* m_query;		// QueryString
	const TCHAR* m_useragent;	// useragent
	HINTERNET hSession;			// 요청 세션

	std::string m_responseBody;

};