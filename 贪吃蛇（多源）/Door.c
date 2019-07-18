#include<stdio.h>
#include<stdlib.h>
#include"Snake.h"

extern score;

void PrintDoor()
{
	setpos(70, 21);
	printf(DOOR);
}

int HasDoor(node* next)
{
	if (next->x == 70 && next->y == 21)
		return 1;
	else
		return 0;
}

void EnterDoor(snake* p2)
{
	p2->status = NextChapter;
}