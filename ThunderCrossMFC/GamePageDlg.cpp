// GamePageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThunderCrossMFC.h"
#include "GamePageDlg.h"
#include "afxdialogex.h"


// GamePageDlg 对话框

IMPLEMENT_DYNAMIC(GamePageDlg, CDialogEx)

GamePageDlg::GamePageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GamePage, pParent)
{

}

GamePageDlg::~GamePageDlg()
{
}

void GamePageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GamePageDlg, CDialogEx)
END_MESSAGE_MAP()


// GamePageDlg 消息处理程序
