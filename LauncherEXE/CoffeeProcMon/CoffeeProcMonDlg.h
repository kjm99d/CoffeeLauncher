
// CoffeeProcMonDlg.h: 헤더 파일
//

#pragma once

#include "CoffeeProcSearch\include\ProcessFinder.h"
#pragma comment(lib, "CoffeeProcSearch.lib")


// CCoffeeProcMonDlg 대화 상자
class CCoffeeProcMonDlg : public CDialogEx
{
// 생성입니다.
public:
	CCoffeeProcMonDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COFFEEPROCMON_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()



private:
    HANDLE m_ProcMonThread; // 실제로 프로세스 모니터링 역할을 하는 스레드의 핸들 값
public:
    CEdit m_EditProc;
    afx_msg void OnBnClickedOk();
};
