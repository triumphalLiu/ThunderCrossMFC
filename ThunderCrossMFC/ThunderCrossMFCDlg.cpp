
// ThunderCrossMFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ThunderCrossMFC.h"
#include "ThunderCrossMFCDlg.h"
#include "afxdialogex.h"
//���ֿ���
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#define PATH "L:\\ThunderCrossMFC\\ThunderCrossMFC\\res\\game_music.wav"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CThunderCrossMFCDlg �Ի���

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


// CThunderCrossMFCDlg ��Ϣ�������

BOOL CThunderCrossMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	PlaySound(TEXT(PATH), NULL, SND_FILENAME | SND_ASYNC); //��ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CThunderCrossMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//��Ϸ����
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

//���ֿ���
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
