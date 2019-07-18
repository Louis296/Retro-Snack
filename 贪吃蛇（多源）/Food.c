#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<mmsystem.h>
#include"Snake.h"
#pragma comment(lib,"winmm.lib")

extern int nodeofsnake;
int eatfoodflag;
eatfoodflag = 0;

void CreateFood(snake* p2)
{
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL);
	p = (node*)malloc(sizeof(node));
	p2->food = (node*)malloc(sizeof(node));
	p2->food->next = NULL;
	p2->food->prev = NULL;
	p1 = p2->snake;
	flag = 1;
	do
	{
		srand(seed);
		while (1)
		{
			p->x = rand() % 40 + 14;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % 20 + 7;//随机生成坐标
		while (p1 != NULL)
		{
			if (p1->x != p->x&&p1->y != p->y)
			{
				p1 = p1->next;
			}
			else
				break;
		}
		if (p1 == NULL)
		{
			flag = 0;
			seed *= 69535;
		}
		else
			seed *= 77463;
		if (p->x == p2->boom->x&&p->y == p2->boom->y)
			flag = 1;
	} while (flag || HasWall(p->x, p->y));
	p2->food->x = p->x;
	p2->food->y = p->y;
}

void PrintFood(snake* p2)
{
	setpos(p2->food->x, p2->food->y);
	Color(10);
	printf(FOOD);
	Color(16);
}

int hasfood(snake* p2, node* next)
{
	if (next->x == p2->food->x&&next->y == p2->food->y)
		return 1;
	else
		return 0;
}

void nofood(snake* p2, node* next)
{
	node *p;
	next->next = p2->snake;
	p2->snake->prev = next;
	p2->snake = next;
	p = p2->tail;
	p2->tail = p2->tail->prev;
	setpos(p->x, p->y);
	printf(" ");
	if (p2->tail != p2->snake)
		p->prev->next = NULL;
	else
		p2->tail->next = NULL;
	free(p);
}

void eatfood(snake* p2, node* next)
{
	next->next = p2->snake;
	p2->snake->prev = next;
	p2->snake = next;
	p2->snake->prev = NULL;
	CreateFood(p2);
	PrintFood(p2);
	nodeofsnake++;
	eatfoodflag++;
}

int NotPrintFood(int x, int y)
{
	char ch[3];
	ch[0] = GetStr(x, y, 1);
	ch[1] = GetStr(x, y, 2);
	ch[2] = '\0';
	if (!strcmp(ch, FOOD))
		return 0;
	else
		return 1;
}
