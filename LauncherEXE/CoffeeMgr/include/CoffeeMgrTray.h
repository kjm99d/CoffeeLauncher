#pragma once
#include <afxdialogex.h>


class CCoffeeMgrTray : public CDialog
{
	// �����Դϴ�.
public:
	CCoffeeMgrTray(HWND hWnd, CWnd* pParent);
	~CCoffeeMgrTray();
	void RegisterTray();

	void SetHWND(HWND hWnd);


protected:
	LRESULT TrayIconMessage(WPARAM wParam, LPARAM lParam);


	// �����Դϴ�.
//private:
//	HWND m_hWnd;

protected:
	DECLARE_MESSAGE_MAP()

};