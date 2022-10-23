#include <pch.h>
#include "CoffeeMgrTray.h"
#include <res/Resource.h>
#include <MessageID.h>

BEGIN_MESSAGE_MAP(CCoffeeMgrTray, CDialog)
	ON_MESSAGE(WM_TRAYICON_MSG, CCoffeeMgrTray::TrayIconMessage)	// TrayIconMessage

END_MESSAGE_MAP()

CCoffeeMgrTray::CCoffeeMgrTray(HWND hWnd, CWnd* pParent) : CDialog(IDD_COFFEEMGR_DIALOG, pParent)
{
	
}

CCoffeeMgrTray::~CCoffeeMgrTray()
{
}

void CCoffeeMgrTray::RegisterTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON_MSG;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	TCHAR strTitle[256];
	GetWindowText( strTitle, sizeof(strTitle));
	
	_tcscpy_s(nid.szTip, strTitle);

	Shell_NotifyIcon(NIM_ADD, &nid);
	SendMessage( WM_SETICON, static_cast<WPARAM>(TRUE), reinterpret_cast<LPARAM>(nid.hIcon));
}

LRESULT CCoffeeMgrTray::TrayIconMessage(WPARAM wParam, LPARAM lParam)
{
	CMenu menu, * pSubMenu;

	switch (lParam)
	{
	case WM_RBUTTONDOWN:
	{
		CMenu menu, * pSubMenu;

		if (!menu.LoadMenu(IDR_MENU_TRAY))
			return 0;
		if (!(pSubMenu = menu.GetSubMenu(0)))
			return 0;

		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();

		// 컨텍스트 메뉴 출력
		pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
		menu.DestroyMenu();

		break;
	}
	}


	return LRESULT();
}

void CCoffeeMgrTray::SetHWND(HWND hWnd)
{
	m_hWnd = hWnd;
}
