#include "self.h"
#include "stdafx.h"

void self::move_to(int X, int Y)
{
	CWnd *pwnd = AfxGetApp()->m_pMainWnd;
	HWND hwnd = pwnd->GetSafeHwnd();
	HWND pict = GetDlgItem(hwnd, IDC_Hero);
	MoveWindow(pict, X, Y, Hero, Hero, TRUE);
}

void self::create(int X, int Y)
{
	self::level = 1;
	self::score = 0;
	self::loc[0] = X;
	self::loc[1] = Y;
	//PrintChar("*", 1, X, Y);	
	self::move_to(X, Y);
}

void self::move(int key)
{
	//PrintChar(" ", 1, self::loc[0], self::loc[1]);//0 ×óÓÒx  1 ÉÏÏÂy
	switch (key)
	{
	case 119: if (self::loc[1] > Hero) self::loc[1] -= Hero; break; //up
	case 115: if (self::loc[1] < SizeY - Hero) self::loc[1] += Hero; break; //down
	case 97:  if (self::loc[0] > Hero / 2) self::loc[0] -= SizeX / 10; break; //left
	case 100: if (self::loc[0] < SizeX - Hero) self::loc[0] += SizeX / 10; break;//right
	}
	//PrintChar("*", 1, self::loc[0], self::loc[1]);
	self::move_to(self::loc[0], self::loc[1]);
}


void self::destroyed()
{

}

self::self()
{
}

self::~self()
{
}
