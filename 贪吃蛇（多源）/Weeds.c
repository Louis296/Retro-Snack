#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Snake.h"

extern int nodeofsnake;
extern int a[10];
extern int Chapter;
extern int time1, time2;

void CreateWeeds(snake* p2, int number)
{
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL) + 10000;
	p = (node*)malloc(sizeof(node));
	p->next = NULL;
	p1 = p2->snake;
	flag = 1;
	do
	{
		srand(seed);
		while (1)
		{
			p->x = rand() % 62 + 10;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % 30 + 5;//随机生成坐标
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
			seed *= 66563;
		}
		else
			seed *= 55321;
		if (p->x == p2->food->x&&p->y == p2->food->y)
			flag = 1;
		if (flag == 0 && HasWall(p->x, p->y) == 0)
		{
			number--;
			p->prev = (node*)malloc(sizeof(node));
			p->prev->next = p;
			p = p->prev;
		}
	} while (flag || HasWall(p->x, p->y) || number != 0);
	p = p->next;
	free(p->prev);   //删除多生成的一节链表
	p->prev = NULL;
	p2->weeds = p;
}

void PrintWeeds(snake* p2)
{
	node* p;
	p = p2->weeds;
	do
	{
		setpos(p->x, p->y);
		Color(4);
		printf(WEEDS);
		Color(16);
		p = p->next;
	} while (p != NULL);
}

int hasweeds(snake* p2, node* next)
{
	node* p;
	p = p2->weeds;
	do
	{
		if (p->x == next->x&&p->y == next->y)
			return 1;
		p = p->next;
	} while (p != NULL);
	return 0;
}

void eatweeds(snake* p2)
{
	static int times;
	node *p, *p1;
	p1 = p2->tail;
	p2->tail = p2->tail->prev;
	setpos(p1->x, p1->y);
	printf(" ");
	p = p2->weeds;
	do
	{
		setpos(p->x, p->y);
		printf(" ");
		p = p->next;
	} while (p != NULL);
	if (p1->prev != NULL)
	{
		p1->prev->next = NULL;
		free(p1);
		CreateWeeds(p2, Chapter);
		PrintWeeds(p2);
	}
	nodeofsnake--;
	ClearProcessBar();
	if (a[1] = 12)
		times = 0;
	else
		times = 100;
	if (times < 10)
		times++;
	if (times = 10 && nodeofsnake != 0)
	{
		a[1] = 10;
		times = 100;
	}
	if (nodeofsnake == 0)
		times = 0;
}

void WeedBlink(snake* p2)
{
	time1++;
	time2++;
	node* p;
	p = p2->weeds;
	if (time1 >= 10 && time1 <= 15)
	{
		do
		{
			setpos(p->x, p->y);
			printf(" ");
			p = p->next;
		} while (p != NULL);
	}
	if (time1 >= 20)
	{
		PrintWeeds(p2);
		time1 = 0;
	}
	if (time2 >= 80)
	{
		p = p2->weeds;
		do
		{
			setpos(p->x, p->y);
			printf(" ");
			p = p->next;
		} while (p != NULL);
		CreateWeeds(p2, Chapter);
		PrintWeeds(p2);
		time2 = 0;
	}
}