
// CoffeeProcMonDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CoffeeProcMon.h"
#include "CoffeeProcMonDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCoffeeProcMonDlg 대화 상자



CCoffeeProcMonDlg::CCoffeeProcMonDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COFFEEPROCMON_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_ProcMonThread = NULL;
}

void CCoffeeProcMonDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_EditProc);
    DDX_Control(pDX, IDC_EDIT2, m_EditPid);
}

BEGIN_MESSAGE_MAP(CCoffeeProcMonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CCoffeeProcMonDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON1, &CCoffeeProcMonDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCoffeeProcMonDlg 메시지 처리기

BOOL CCoffeeProcMonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCoffeeProcMonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCoffeeProcMonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCoffeeProcMonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void* LoadLibTest() {
    HMODULE mod = LoadLibraryA("CoffeeLicense.dll");
    if (mod)
    {
        ::MessageBoxA(NULL, "Load Lib Success", "FF", MB_OK);
    }
    else
    {
        ::MessageBoxA(NULL, "Load Lib Failure", "FF", MB_OK);

    }

    return NULL;
}

void CCoffeeProcMonDlg::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    //CDialogEx::OnOK();

    CString csProc;
    m_EditProc.GetWindowTextW(csProc);

    const LPWSTR wcsProc = csProc.GetBuffer();
    const int nLenProc = csProc.GetLength();

    size_t memSize = sizeof(char) * nLenProc + 1;
    char* tempProc = (char*)malloc(memSize);
    memset(tempProc, 0x00, memSize);

    // 멀티바이트를 구한다.
    WideCharToMultiByte(CP_UTF8, 0, wcsProc, nLenProc, tempProc, nLenProc, NULL, NULL);




    const BOOL isFindProc = FindProcessByName(tempProc);
    MessageBox(isFindProc ? L"Find !" : L"Not Found !", L"Caption");

    
    
}


void CCoffeeProcMonDlg::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString csPid;
    m_EditPid.GetWindowTextW(csPid);

    DWORD dwPid = _ttoi(csPid.GetBuffer());

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPid);
    if (hProcess)
    {

        // DLL 로딩 함수 구하고 
        HMODULE hKernel32 = LoadLibrary(L"Kernel32.dll");
        if (!hKernel32)
        {
            OutputDebugString(_T("Error: LoadLibrary Kernel32.dll "));
        }
        FARPROC lpfnLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");

        // 프로세스 핸들로해서 힙 공간 만들고
        LPVOID dllPathAlloc = VirtualAllocEx(hProcess, NULL, sizeof(WCHAR) * MAX_PATH, MEM_COMMIT, PAGE_READWRITE);
        if (dllPathAlloc == NULL)
        {
            MessageBox(_T("Error: VirtualAllocEx  ", L"Alert Error", MB_ICONERROR));
        }
        else
        {
            // 메모리 공간 할당에 성공하면


            // 해당 메모리 공간에 문자열 정보 써준다음
            const char* dll = "CoffeeLicense.dll";
            int nLenDLL = strlen(dll);
            if (!WriteProcessMemory(hProcess, dllPathAlloc, dll, nLenDLL, NULL))
            {
                OutputDebugString(_T("Error: WriteProcessMemory  "));
            }

            HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpfnLoadLibrary, dllPathAlloc, NULL, NULL);

            if (hThread == NULL)
            {
                MessageBox(L"CreateRemoteThread Failure");
            }


        }
     
        

        
    }
    else
    {
        MessageBox(L"OpenProcess Failure", L"Alert Error", MB_ICONERROR);
    }
}
