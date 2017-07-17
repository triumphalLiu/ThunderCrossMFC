#include "stdafx.h"
#include "common.h"
#include "self.h"
#include "enemy.h"
#include "bullet.h"
#pragma warning (disable:4996)

self plane; //新建己方对象
enemy Enemy;
bullet Bullet; //新建子弹对象

int wait();
int enemy_born()
{
	int x = (rand() * rand()) % (SizeX / SizeEnemy - 2);
	x *= SizeEnemy;
	x += SizeEnemy * 3 / 2;
	Enemy.head = Enemy.create(Enemy.head, x);
	//TODO:敌机射击功能暂时关闭，待图片加载优化完成再打开
	//Bullet.head = Bullet.add(Bullet.head, x+SizeEnemy/2, 2*SizeEnemy, 0);
	return 0;
}

int enemy_moveshot()
{
	//敌机移动及射击
	Enemy.head = Enemy.move(Enemy.head);
	/*
	for (int i = 0; i < Enemy.count; ++i)
	{
	int x = Enemy.getinfo(i, 0);
	int y = Enemy.getinfo(i, 1);
	if (x != -1)
		Bullet.head = Bullet.add(Bullet.head, x, y, 0);
	}
	*/
	return 0;
}

int shot()
{
	Bullet.head = Bullet.move(Bullet.head);
	return 0;
}
#define LEVEL_GAP 5
#define MAX_LEVEL 5 //WARNING 修改此值后 记得修改下面的数组
int born_time[] = {-1, 1500, 1200, 1000, 800, 600 };
int move_time[] = {-1, 500, 400, 300, 200, 100 };
void play(CWnd *pause)
{
	srand((unsigned)time(0));
	//游戏开始
	MSG msg;
	CWnd *cwnd = AfxGetApp()->m_pMainWnd;
	plane.create((SizeX - Hero), SizeY - Hero); //初始化飞机
	cwnd->SetTimer(1, 5, NULL);
	cwnd->SetTimer(2, born_time[plane.level], NULL);
	cwnd->SetTimer(3, move_time[plane.level], NULL);
	bool exit_game = 0;
	Bullet.init();
	Enemy.init();
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//读取键盘消息
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (msg.message == WM_KEYDOWN)
			{
				unsigned key = msg.wParam;
				switch (key) {
				case 27:  exit_game = 1; break; //ESC
				case 'A': 
				case 'W': 
				case 'D': 
				case 'S': plane.move(key + 32); break;
				case 'P': 
					pause->ShowWindow(SW_SHOW);
					exit_game = wait();
					pause->ShowWindow(SW_HIDE);
					break;
				case 'H': 
					Bullet.head = Bullet.add(Bullet.head, plane.loc[0] + (Hero + BulletX / 2) / 2, plane.loc[1] - BulletY, 1); break;
				/*
				case 'M':
					Bullet.head = Bullet.move(Bullet.head); break;
				
				case 'I':
					//For Debug
					while (p != NULL)
					{
						p = p->next;
					}break;*/
				default: break; //MessageBox(msg.hwnd, L"Other", 0, 0); break;
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			int last_level = plane.level;
			plane.level = plane.level < MAX_LEVEL ? plane.score / LEVEL_GAP + 1 : MAX_LEVEL;	//升级
			if (plane.level <= 5 && last_level != plane.level)
			{
				cwnd->KillTimer(2);
				cwnd->KillTimer(3);
				cwnd->SetTimer(2, born_time[plane.level], NULL);
				cwnd->SetTimer(3, move_time[plane.level], NULL);
			}
			//判断自己是否被子弹打中
			if (0 == Bullet.check(Bullet.head, plane.loc[0], plane.loc[1], 1))
				break;
			
			//判断子弹是否打中敌机
			for (int i = 0; i < Enemy.count; ++i)
			{
				int x = Enemy.getinfo(i, 0);
				int y = Enemy.getinfo(i, 1);
				if (x != -1 && 0 == Bullet.check(Bullet.head, x, y, 0))
				{
					Enemy.head = Enemy.destroyed(i);
					--i;
					plane.score++;
				}
			}
			//判断有没有碰到敌机
			if (0 == Enemy.check(Enemy.head, plane.loc[0], plane.loc[1]))
				break;
			
		}
		if (exit_game)
			break;
	}
	cwnd->KillTimer(1);
	cwnd->KillTimer(2);
	cwnd->KillTimer(3);
	CString buffer;
	buffer.Format(_T("你的分数是%d, 最高关卡是%d"), plane.score, plane.level);
	AfxMessageBox(buffer);
	//游戏结束
}

int wait()
{
	MSG msg;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//读取键盘消息
			if (msg.message == WM_QUIT)
				break;
			else if (msg.message == WM_KEYDOWN)
			{
				unsigned key = msg.wParam;
				switch (key) {
				case 27:  return 1; //ESC
				case 'P': return 0;
				default: break;
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 1;
}