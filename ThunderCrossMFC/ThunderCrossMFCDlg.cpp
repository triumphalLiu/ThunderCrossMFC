#include "stdafx.h"
#include "ThunderCrossMFC.h"
#include "ThunderCrossMFCDlg.h"
#include "afxdialogex.h"
#include "common.h"
//���ֿ���
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

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
	ON_WM_TIMER()
END_MESSAGE_MAP()


//��ȡͼƬ�ṹ��
struct PhotoInfo {
	BITMAPINFO *pBmpInfo;       //��¼ͼ��ϸ��
	BYTE *pBmpData;             //ͼ������
	BITMAPFILEHEADER bmpHeader; //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;   //��Ϣͷ
	CFile bmpFile;              //��¼���ļ�
	char *path;
	PhotoInfo *next;
};
PhotoInfo *photohead = NULL;
PhotoInfo *load_photo(PhotoInfo *head, char *path);

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
	PlaySound(TEXT(PATH_MUSIC), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //��ʼ������
	photohead = load_photo(photohead, PATH_BACK);
	photohead = load_photo(photohead, PATH_BULLET);
	photohead = load_photo(photohead, PATH_ENEMY);
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
extern void play(CWnd *);
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
	//���ز��������
	CEdit *edit = (CEdit*)GetDlgItem(IDC_Hero);
	edit->ShowWindow(SW_SHOW);
	//��ʾ�й�����
	CWnd *pwnd = GetDlgItem(IDC_Pause);
	play(pwnd);
	//������ʾ�������
	CEdit *edit_back = (CEdit*)GetDlgItem(IDC_STATIC);
	edit_back->ShowWindow(SW_HIDE);
	edit_back->ShowWindow(SW_SHOW);
	edit0->ShowWindow(SW_SHOW);
	edit1->ShowWindow(SW_SHOW);
	edit2->ShowWindow(SW_SHOW);
	edit3->ShowWindow(SW_SHOW);
	edit->ShowWindow(SW_HIDE);
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
	PlaySound(TEXT(PATH_MUSIC), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	CEdit *edit1 = (CEdit*)GetDlgItem(IDC_SoundToOn);
	edit1->ShowWindow(SW_HIDE);
	CEdit *edit2 = (CEdit*)GetDlgItem(IDC_SoundToOFF);
	edit2->ShowWindow(SW_SHOW);
	sound = 1;
}

//��̬ͼƬ����

PhotoInfo *load_photo(PhotoInfo *head, char *path)
{
	CString name(path);
	PhotoInfo *p = new PhotoInfo;
	p->next = NULL;
	if (!p->bmpFile.Open(name, CFile::modeRead | CFile::typeBinary))
		return NULL;
	if (p->bmpFile.Read(&p->bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return NULL;
	if (p->bmpFile.Read(&p->bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return NULL;
	p->pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//Ϊͼ����������ռ�
	memcpy(p->pBmpInfo, &p->bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = p->bmpHeader.bfSize - p->bmpHeader.bfOffBits;
	p->pBmpData = (BYTE*)new char[dataBytes];
	p->bmpFile.Read(p->pBmpData, dataBytes);
	p->bmpFile.Close();
	p->path = (char *)malloc(sizeof(char) * 200);
	strcpy(p->path, path);
	if (photohead == NULL)
		photohead = p;
	else
	{
		p->next = photohead;
		photohead = p;
	}
	return photohead;
}

CDC *CThunderCrossMFCDlg::AddPhotoActively(char *path, int X, int Y, int flag)
{
	//��ʾͼ��
	CWnd *pWnd = AfxGetApp()->m_pMainWnd; //���pictrue�ؼ����ڵľ��
	CDC *pDC = pWnd->GetDC(); //���pictrue�ؼ���DC
	pDC->SetStretchBltMode(COLORONCOLOR);
	PhotoInfo *p = photohead;
	while (p != NULL)
	{
		if (strcmp(p->path,path) == 0)
			break;
		else p = p->next;
	}
	if(path == PATH_BULLET)
		StretchDIBits(pDC->GetSafeHdc(), X, Y, BulletX, BulletY, 0, 0,
			p->bmpInfo.biWidth, p->bmpInfo.biHeight, p->pBmpData, p->pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
	else if(path == PATH_ENEMY)
		StretchDIBits(pDC->GetSafeHdc(), X, Y, SizeEnemy, SizeEnemy, 0, 0,
			p->bmpInfo.biWidth, p->bmpInfo.biHeight, p->pBmpData, p->pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
	else if(path == PATH_BACK && flag == 0)
		StretchDIBits(pDC->GetSafeHdc(), X, Y, BulletX, BulletY, X - 2 * BulletX, SizeY - Y,
			BulletX, BulletY, p->pBmpData, p->pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
	else if(path == PATH_BACK && flag == 1)
		StretchDIBits(pDC->GetSafeHdc(), X, Y, SizeEnemy, SizeEnemy, X, Y,
			SizeEnemy, SizeEnemy, p->pBmpData, p->pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
	return pDC;
}

extern int enemy_born();
extern int enemy_moveshot();
extern int shot();
void CThunderCrossMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1: shot(); break;
	case 2: enemy_born(); break;
	case 3: enemy_moveshot(); break;
	default:break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
