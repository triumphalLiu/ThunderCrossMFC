#include "stdafx.h"
#include "common.h"
#include "self.h"
#include "enemy.h"
#include "bullet.h"
#pragma warning (disable:4996)

int gap[6] = { 1000,800,600,400,200,80 };

void play()
{
	srand((unsigned)time(0));
	//游戏开始
	MSG msg;
	bool exit_game = 0;
	/*
	self plane; //新建己方对象
	plane.create((SizeX - Hero) / 2, SizeY - Hero); //初始化飞机

	bullet Bullet; //新建子弹对象
	Bullet.init();
	enemy Enemy;
	Enemy.init();
	*/
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
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
				case 'S': //plane.move(key + 32); break;
				case 'H': //Bullet.head = Bullet.add(Bullet.head, plane.loc[0], plane.loc[1], 1);break;
				default:  MessageBox(msg.hwnd, L"Other", 0, 0); break;
				}
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			/*
			plane.level = plane.score / 20;	//升级
			if (0 == Enemy.check(Enemy.head, plane.loc[0], plane.loc[1]))
				break;
			//设定固定的时间
			Sleep(1);
			Bullet.count += 1;
			if (Bullet.count % 20 == 0)
			{
				//子弹移动
				Bullet.move(Bullet.head);
				//判断子弹是否打中
				if (0 == Bullet.check(Bullet.head, plane.loc[0], plane.loc[1], 1))
					break;
				for (int i = 0; i < Enemy.count; ++i)
				{
					int x = Enemy.getinfo(i, 0);
					int y = Enemy.getinfo(i, 1);
					if (x != -1 && 0 == Bullet.check(Bullet.head, x, y, 0))
					{
						Enemy.head = Enemy.destroyed(i);
						plane.score++;
					}
				}
				//敌机移动及生成
				if (Bullet.count == gap[plane.level] / 2)
				{
					Enemy.move(Enemy.head);
					for (int i = 0; i < Enemy.count; ++i)
					{
						int x = Enemy.getinfo(i, 0);
						int y = Enemy.getinfo(i, 1);
						if (x != -1)
							Bullet.head = Bullet.add(Bullet.head, x, y, 0);
					}
				}
				if (Bullet.count == gap[plane.level]) //生成敌机
				{
					int x = (rand() * rand()) % SizeX;
					Enemy.head = Enemy.create(Enemy.head, x);
					Bullet.head = Bullet.add(Bullet.head, x, 0, 0);
					Bullet.count = 0;
				}
			}
			*/	
		}
		if (exit_game)
			break;
	}
	CString buffer;
	buffer.Format(_T("你的分数是1"));
	AfxMessageBox(buffer);
	//游戏结束
}