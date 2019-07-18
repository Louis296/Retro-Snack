#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"Snake.h"

extern int nodeofsnake;
extern int boomflag;
extern int a[10];
extern int Chapter;

void CreateBoom(snake* p2, int number)
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
			seed *= 44997;
		}
		else
			seed *= 85932;
		if (p->x == p2->food->x&&p->y == p2->food->y)
			flag = 1;
		if (p->x == p2->weeds->x&&p->y == p2->weeds->y)
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
	p2->boom = p;
}

void PrintBoom(snake* p2)
{
	node* p;
	p = p2->boom;
	do
	{
		setpos(p->x, p->y);
		Color(15);
		printf(BOOM);
		Color(16);
		p = p->next;
	} while (p != NULL);
}

int hasboom(snake* p2, node* next)
{
	node* p;
	p = p2->boom;
	do
	{
		if (p->x == next->x&&p->y == next->y)
			return 1;
		p = p->next;
	} while (p != NULL);
	return 0;
}

void touchboom(snake* p2)
{
	int i;
	static int times;
	node *p, *p1, *p3;
	p1 = p = p2->snake;
	if (p1->prev != NULL || p1->next != NULL)
	{
		for (i = 1; i <= nodeofsnake / 2; i++)
		{
			p = p->next;
		}
		p2->snake = p;
		p->prev->next = NULL;
		p->prev = NULL;
		p3 = p1;
		do     //消除被炸掉的蛇身
		{
			setpos(p3->x, p3->y);
			printf(" ");
			p3 = p3->next;
		} while (p3 != NULL);
		if (p1->next == NULL)  //释放了被炸掉的蛇身内存（炸掉一节的特殊情况）
			free(p1);
		else
		{
			p = p1->next;
			while (p->next != NULL && p != NULL)  //释放了被炸掉的蛇身内存
			{
				free(p->prev);
				p = p->next;
			}
			free(p);
		}
		p = p2->boom;
		do
		{
			setpos(p->x, p->y);
			printf(" ");
			p = p->next;
		} while (p != NULL);
		CreateBoom(p2, Chapter);
		PrintBoom(p2);
	}
	if (nodeofsnake == 1)
	{
		boomflag = 1;
		nodeofsnake = 0;
		times = 0;
	}
	nodeofsnake -= nodeofsnake / 2;
	ClearProcessBar();
	if (a[0] = 12)
		times = 0;
	else
		times = 100;
	if (times < 5)
		times++;
	if (times = 5 && nodeofsnake != 0)
	{
		a[0] = 10;
		times = 100;
	}
	if (nodeofsnake == 0)
		times = 0;
}

void RePrintBoom(snake* p2)
{
	node* p;
	p = p2->boom;
	do
	{
		char ch[3];
		ch[0] = GetStr(p->x, p->y, 1);
		ch[1] = GetStr(p->x, p->y, 2);
		ch[2] = '\0';
		if (!strcmp(ch, BOOM))
		{
			Color(15);
			setpos(p->x, p->y);
			printf(BOOM);
		}
		p = p->next;
	} while (p != NULL);
}
