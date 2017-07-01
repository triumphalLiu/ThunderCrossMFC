
// ThunderCrossMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThunderCrossMFC.h"
#include "ThunderCrossMFCDlg.h"
#include "afxdialogex.h"
//音乐控制
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#define PATH "L:\\ThunderCrossMFC\\ThunderCrossMFC\\res\\game_music.wav"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CThunderCrossMFCDlg 对话框

CThunderCrossMFCDlg::CThunderCrossMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_THUNDERCROSSMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThunderCrossMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThunderCrossMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_StartGame, &CThunderCrossMFCDlg::OnStnClickedStartgame)
	ON_STN_CLICKED(IDC_SoundToOFF, &CThunderCrossMFCDlg::OnStnClickedSoundtooff)
	ON_STN_CLICKED(IDC_SoundToOn, &CThunderCrossMFCDlg::OnStnClickedSoundtoon)
	ON_STN_CLICKED(IDC_ExitGame, &CThunderCrossMFCDlg::OnStnClickedExitgame)
END_MESSAGE_MAP()


// CThunderCrossMFCDlg 消息处理程序

BOOL CThunderCrossMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	PlaySound(TEXT(PATH), NULL, SND_FILENAME | SND_ASYNC); //初始化声音
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CThunderCrossMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThunderCrossMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CThunderCrossMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//游戏控制
extern void play();
void CThunderCrossMFCDlg::OnStnClickedStartgame()
{
	CEdit *edit0 = (CEdit*)GetDlgItem(IDC_StartGame);
	edit0->ShowWindow(SW_HIDE);
	CEdit *edit1 = (CEdit*)GetDlgItem(IDC_GameIcon);
	edit1->ShowWindow(SW_HIDE);
	CEdit *edit2 = (CEdit*)GetDlgItem(IDC_GameName);
	edit2->ShowWindow(SW_HIDE);
	CEdit *edit3 = (CEdit*)GetDlgItem(IDC_ExitGame);
	edit3->ShowWindow(SW_HIDE);
	play(); 
	edit0->ShowWindow(SW_SHOW);
	edit1->ShowWindow(SW_SHOW);
	edit2->ShowWindow(SW_SHOW);
	edit3->ShowWindow(SW_SHOW);
}

void CThunderCrossMFCDlg::OnStnClickedExitgame()
{
	DestroyWindow();
	exit(0);
}

//音乐控制
bool sound = 1;

void CThunderCrossMFCDlg::OnStnClickedSoundtooff()
{
	PlaySound(NULL, NULL, SND_FILENAME);
	CEdit *edit1 = (CEdit*)GetDlgItem(IDC_SoundToOFF);
	edit1->ShowWindow(SW_HIDE);
	CEdit *edit2 = (CEdit*)GetDlgItem(IDC_SoundToOn);
	edit2->ShowWindow(SW_SHOW);
	sound = 0;
}

void CThunderCrossMFCDlg::OnStnClickedSoundtoon()
{
	PlaySound(TEXT(PATH), NULL, SND_FILENAME | SND_ASYNC);
	CEdit *edit1 = (CEdit*)GetDlgItem(IDC_SoundToOn);
	edit1->ShowWindow(SW_HIDE);
	CEdit *edit2 = (CEdit*)GetDlgItem(IDC_SoundToOFF);
	edit2->ShowWindow(SW_SHOW);
	sound = 1;
}
