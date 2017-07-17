
// ThunderCrossMFCDlg.h : ͷ�ļ�
//

#pragma once


// CThunderCrossMFCDlg �Ի���
class CThunderCrossMFCDlg : public CDialogEx
{
// ����
public:
	CThunderCrossMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THUNDERCROSSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStartgame();
	afx_msg void OnStnClickedSoundtooff();
	afx_msg void OnStnClickedSoundtoon();
	afx_msg void OnStnClickedExitgame();
	CDC*AddPhotoActively(char *path, int X, int Y, int flag); 
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStnClickedHelp();
	afx_msg void OnStnClickedHelppage();
	afx_msg void OnStnClickedWatchsc();
};
