#pragma once


// GamePageDlg �Ի���

class GamePageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GamePageDlg)

public:
	GamePageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GamePageDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GamePage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
