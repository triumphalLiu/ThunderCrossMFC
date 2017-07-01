#include "bullet.h"
#include "stdafx.h"
/*void bullet::end()
{
while (bullet::head != NULL)
{
Bair *temp = bullet::head;
Bair *new_head = bullet::head->next;
bullet::del(temp, bullet::head);
bullet::head = new_head;
}
}*/

void bullet::init()
{
	bullet::count = 0;
	bullet::head = NULL;
}

Bair *bullet::add(Bair *head, int x, int y, int flag)
{
	Bair *p = new Bair;
	p->flag = flag;
	p->loc[0] = x;
	if (flag == 1)
		p->loc[1] = y - 1;
	else p->loc[1] = y + 1;
	p->next = NULL;
	if (head == NULL)
		head = p;
	else
	{
		p->next = head;
		head = p;
	}
	//PrintChar("|", 1, p->loc[0], p->loc[1]);
	CThunderCrossMFCDlg newbullet;
	head->pdc = newbullet.AddPhotoActively(PATH_BULLET, x, y);
	return head;
}
Bair *bullet::del(Bair *node, Bair *head)
{
	if (node == head)
	{
		head = NULL;
	}
	else
	{
		Bair *p = head;
		while (p->next != node)
		{
			p = p->next;
		}
		Bair *del = p->next;
		p->next = del->next;
		free(del);
	}
	return head;
}

Bair *bullet::move(Bair *head)
{
	Bair *p = head;
	while (p != NULL)
	{
		//PrintChar(" ", 1, p->loc[0], p->loc[1]);
		if (p->flag == 1)
			p->loc[1] -= 1;
		else if (p->flag == 0)
			p->loc[1] += 1;
		Bair *n = p->next;
		if (p->loc[1] == -1 || p->loc[1] == 81)
		{
			head = bullet::del(p, head);
			if (head == NULL)
				return head;
		}
		else
		{
			//PrintChar("|", 1, p->loc[0], p->loc[1]);
		}
		p = n;
	}
	return head;
}
bool bullet::check(Bair *&head, int x, int y, int flag)  // dead=0
{
	Bair *p = head;
	while (p != NULL)
	{
		if (p->flag | flag && p->loc[0] == x && p->loc[1] == y)
		{
			head = bullet::del(p, head);
			return 0;
		}
		p = p->next;
	}
	return 1;
}
bullet::bullet()
{
}
bullet::~bullet()
{
}