#pragma once
#include "common.h"

class self
{
public:
	self();
	~self();
	int score;
	int level;
	int loc[2];
	void create(int X, int Y);
	void destroyed();
	void move(int key);
private:

};

//extern void PrintChar(char *ch, UINT count, UINT x, UINT y);

void self::create(int X, int Y)
{
	self::level = 1;
	self::score = 0;
	self::loc[0] = X;
	self::loc[1] = Y;
	//PrintChar("*", 1, X, Y);


}

void self::move(int key)
{
	//PrintChar(" ", 1, self::loc[0], self::loc[1]);//0 ×óÓÒx  1 ÉÏÏÂy
	switch (key)
	{
	case 119: if (self::loc[1] > 0) self::loc[1] -= 1; break; //up
	case 115: if (self::loc[1] < SizeY) self::loc[1] += 1; break; //down
	case 97:  if (self::loc[0] > 0) self::loc[0] -= 1; break; //left
	case 100: if (self::loc[0] < SizeX) self::loc[0] += 1; break;//right
	}
	//PrintChar("*", 1, self::loc[0], self::loc[1]);
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
