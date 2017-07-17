
// ThunderCrossMFCDlg.h : 头文件
//

#pragma once


// CThunderCrossMFCDlg 对话框
class CThunderCrossMFCDlg : public CDialogEx
{
// 构造
public:
	CThunderCrossMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THUNDERCROSSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
