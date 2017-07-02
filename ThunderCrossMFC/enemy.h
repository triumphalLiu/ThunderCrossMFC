#pragma once
#include "common.h"

struct Eair {
	int loc[2];
	Eair *next;
};

class enemy
{
public:
	enemy();
	~enemy();
	Eair *head;
	int count;
	void init();
	int getinfo(int, int);
	Eair *create(Eair *head, int x);
	Eair *destroyed(int);
	Eair *move(Eair *head);
	int check(Eair *head, int x, int y);
private:

};

//extern void PrintChar(char *ch, UINT count, UINT x, UINT y);

void enemy::init()
{
	enemy::head = NULL;
	enemy::count = 0;
}

Eair *enemy::create(Eair *head, int x)
{
	int y = 50;
	Eair *p = new Eair;
	p->loc[0] = x;
	p->loc[1] = y;
	p->next = NULL;
	if (head == NULL)
		head = p;
	else
	{
		p->next = head;
		head = p;
	}
	//PrintChar("#", 1, p->loc[0], p->loc[1]);
	CThunderCrossMFCDlg newbullet;
	newbullet.AddPhotoActively(PATH_ENEMY, x, y, 1);
	++enemy::count;
	return head;
}

Eair *enemy::move(Eair *head)
{
	CThunderCrossMFCDlg newbullet;
	Eair *p = head;
	int  i = 0;
	while (p != NULL)
	{
		//PrintChar(" ", 1, p->loc[0], p->loc[1]);
		newbullet.AddPhotoActively(PATH_BACK, p->loc[0], p->loc[1], 1);
		p->loc[1] += SizeEnemy / 2;
		Eair *nxt = p->next;
		if (p->loc[1] >= 800)
		{
			head = enemy::destroyed(i);
			i--;
		}
		//PrintChar("#", 1, p->loc[0], p->loc[1]);
		else
			newbullet.AddPhotoActively(PATH_ENEMY, p->loc[0], p->loc[1], 1);
		p = nxt;
		++i;
	}
	return head;
}

int enemy::getinfo(int i, int option)
{
	Eair *p = enemy::head;
	for (int j = 0; j < i && p != NULL; ++j)
		p = p->next;
	if (p == NULL)
		return -1;
	else
		return p->loc[option];
}

Eair *enemy::destroyed(int i)
{
	--enemy::count;
	Eair *p = enemy::head;
	if (i == 0)
	{
		enemy::head = p->next;
		int x = p->loc[0];
		int y = p->loc[1];
		//PrintChar(" ", 1, x, y);
		free(p);
		return enemy::head;
	}
	for (int j = 0; j < i - 1; ++j)
		p = p->next;
	Eair *del = p->next;
	p->next = del->next;
	int x = del->loc[0];
	int y = del->loc[1];
	//PrintChar(" ", 1, x, y);
	free(del);
	return enemy::head;
}

int enemy::check(Eair *head, int x, int y)
{
	Eair *p = head;
	while (p != NULL)
	{
		if (p->loc[1] >= 40 || (p->loc[0] == x && p->loc[1] == y))
			return 0;
		p = p->next;
	}
	return 1;
}

enemy::enemy()
{
}

enemy::~enemy()
{
}