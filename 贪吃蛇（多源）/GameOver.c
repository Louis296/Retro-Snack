#include<stdio.h>
#include<windows.h>
#include<string.h>
#include"Snake.h"

extern int nodeofsnake;
extern int boomflag;
extern int Chapter;
extern int a[10];
extern int eatfoodflag;
int killbywallflag;
killbywallflag = 0;
enum Dir dirflag;
dirflag = NONE;
int times;   //防止蛇被误认为撞到墙

char GetStr(int x, int y, int station)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	char str[3] = { 0 };
	DWORD read;
	ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), str, 2, pos, &read);
	if (station == 1)
		return str[0];
	if (station == 2)
		return str[1];
}

int killbywall(snake* p2)
{
	node* next;
	next = (node*)malloc(sizeof(node));
	next->x = p2->snake->x;
	next->y = p2->snake->y;
	switch (p2->dir)
	{
	case UP:
		next->y -= 1;
		break;
	case DOWN:
		next->y += 1;
		break;
	case LEFT:
		next->x -= 2;
		break;
	case RIGHT:
		next->x += 2;
		break;
	}
	char ch[3];
	ch[0] = GetStr(next->x, next->y, 1);
	ch[1] = GetStr(next->x, next->y, 2);
	ch[2] = '\0';
	if (killbywallflag == 1 && p2->dir == dirflag && times)
		return 1;
	times = 0;
	dirflag = NONE;
	killbywallflag = 0;
	if (!strcmp(ch, WALL))
	{
		killbywallflag = 1;
		dirflag = p2->dir;
		times=1;
	}
	return 0;
}

int killbyweed(snake* p2)
{
	if (p2->snake->next == NULL && p2->snake->prev == NULL && nodeofsnake == 0)
		return 1;
	else
		return 0;
}

int killbyboom(snake* p2)
{
	if (p2->snake->next == NULL && p2->snake->prev == NULL && nodeofsnake == 0 && boomflag == 1)
		return 1;
	else
		return 0;
}

void GameOver(snake* p2)
{
	if (killbywall(p2))
	{
		PrintWindows(12, END);
		p2->status = WallKill;
		Color(12);
		setpos(40, 20);
		printf("游戏结束！");
		setpos(37, 22);
		printf("死因：撞墙而死！");
		setpos(31, 24);
		printf("按F1重新开始，ESC返回主界面.");
		Color(16);
		killbywallflag = 0;
		dirflag = NONE;
	}
	if (killbyweed(p2))
	{
		PrintWindows(12, END);
		p2->status = WeedsKill;
		Color(12);
		setpos(40, 20);
		printf("游戏结束！");
		setpos(37, 22);
		printf("死因：毒草毒死！");
		setpos(31, 24);
		printf("按F1重新开始，ESC返回主界面.");
		Color(16);
	}
	if (killbyboom(p2))
	{
		PrintWindows(12, END);
		p2->status = BoomKill;
		Color(12);
		setpos(40, 20);
		printf("游戏结束！");
		setpos(37, 22);
		printf("死因：被炸死！");
		setpos(31, 24);
		printf("按F1重新开始，ESC返回主界面.");
		Color(16);
	}
	if (p2->status == SelfKill)
	{
		PrintWindows(12, END);
		Color(12);
		setpos(40, 20);
		printf("游戏结束！");
		setpos(37, 22);
		printf("死因：吃到自身！");
		setpos(31, 24);
		printf("按F1重新开始，ESC返回主界面.");
		Color(16);
	}
	if (eatfoodflag == 0)
		a[2] = 10;
}
