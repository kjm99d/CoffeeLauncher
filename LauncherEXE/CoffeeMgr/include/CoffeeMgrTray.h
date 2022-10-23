#pragma once
#include <afxdialogex.h>


class CCoffeeMgrTray : public CDialog
{
	// 생성입니다.
public:
	CCoffeeMgrTray(HWND hWnd, CWnd* pParent);
	~CCoffeeMgrTray();
	void RegisterTray();

	void SetHWND(HWND hWnd);


protected:
	LRESULT TrayIconMessage(WPARAM wParam, LPARAM lParam);


	// 구현입니다.
//private:
//	HWND m_hWnd;

protected:
	DECLARE_MESSAGE_MAP()

};