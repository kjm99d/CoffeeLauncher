#pragma once

#ifdef WINHTTPCOMM_EXPORTS
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#else
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#endif

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
typedef std::vector<std::pair<const wchar_t*, const wchar_t*>> request_header;

/*
* @brief 에러정보를 저장하는 열거형.
*/
typedef enum {
	ERROR_NONE = 0,
} RequestError;

/*
* @brief 에러값을 문자열로 반환 해주는 함수.
* 
* @param err - CRequest의 Public Object 호출을 통해 반환받은 정보
*/
const char* GetRequestErrorString(RequestError err);

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
	CRequest() = default;
	CRequest(const CRequest&) = delete;
	~CRequest();

public:
	/**
	 * @brief 세션을 열고 동작에 필요한 URL 정보를 파싱하는 함수.
	 * 
	 * 
	 * \param method - RequestMethod Enum 값으로 설정된 열거 타입으로 지정되어 있음.
	 * \param url - 요청하고자 하는 웹서버의 주소정보.
	 */
	void Open(RequestMethod method, const wchar_t* url);

	/**
	 * \brief 요청헤더를 설정합니다.
	 *
	 * \param key - 헤더의 키값
	 * \param value - 헤더의 밸류값
	 */
	void SetHeader(const wchar_t* key, const wchar_t* value);

	


	/**
	 * @brief ResponseBody Byte 정보를 전달받는 함수.
	 * @brief 읽을 데이터가 남아 있을 경우 반환 값이 True 이다.
	 * 
	 * 
	 * \param pbBufferStorage - PBYTE 형태로 정의된 변수를 입력으로 받아 포인터를 전달 받는다.
	 * \param dwReadDataSize - DWORD 형태로 정의된 변수를 입력 받아, 서버를 통해 전달 받은 데이터의 크기를 가져온다.
	 * \return 
	 */
	BOOL GetBuffer(PBYTE& pbBufferStorage, DWORD& dwReadDataSize);

	/**
	 * Send(...) 함수 호출 이후, 응답상태 코드를 반환한다..
	 * 
	 * \return Response Header Status Code
	 */
	DWORD GetStatusCode();

	/**
	 * Request Header의 Context-Type 정보를 application/x-www-form-urlencoded 방식으로 호출하는 함수.
	 * 
	 */
	void Send();

	/**
	 * GET을 제외한 다른 메소드 사용 시, Payload 정보를 전달하는 함수.
	 * 
	 * \param strForm - Payload 정보
	 */
	void Send(const wchar_t* strForm);




protected:
	/**
	 * 현재 설정된 요청 메소드를 기반으로 문자열화된 요청 메소드를 전달합니다.
	 * 
	 * \return 
	 */
	const wchar_t* StrRequestMethodW(const RequestMethod method = kGET);

	/**
	 * 서버에 실제로 요청을 하는 함수.
	 * 
	 * \param szForm - Payload 정보  (MultiByte로 처리됨)
	 * \param nLenForm - Payload의 길이
	 */
	void Send(char* szForm, int nLenForm);
	

protected:
	request_header m_headers;
	RequestMethod m_method;		// 요청 메소드 타입
	wchar_t m_url[4096];			// 요청 URL
	HINTERNET hSession;			// 요청 세션

	
	//std::string m_responseBody;


private:
	void CreateSession(const wchar_t * session = NULL);
	void SetComponent(const wchar_t* url);


	void Close();


private:
	BYTE           m_ResponseBuffer[4096];
	URL_COMPONENTS m_urlComponents;
	WCHAR          m_szHostName[256], m_szUrlPath[2048];
	HINTERNET      m_hConnect, m_hRequest;
	DWORD m_dwStatusCode;


};