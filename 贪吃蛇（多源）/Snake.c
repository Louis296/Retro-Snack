#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"Snake.h"

extern int nodeofsnake;
extern int snakeskin;
extern int score;
extern int colorflow;
extern int Chapter;
extern int killbywallflag;
extern enum Dir dirflag;
extern int times;

void CreateSnake(snake* p2,int snakenode,int x,int y)
{
	node *head, *p, *p1;
	head = (node*)malloc(sizeof(node));
	head->prev = NULL;
	head->x = x;
	head->y = y;
	p = head;
	int i;
	for (i = 1; i < snakenode; i++)
	{
		p1 = (node*)malloc(sizeof(node));
		p1->prev = p;
		p->next = p1;
		p1->x = p->x + 2;
		p1->y = p->y;
		p1->next = NULL;
		p = p1;
	}
	p2->snake = head;
	p2->dir = LEFT;
	p2->status = Ready;
	p2->tail = p1;
	nodeofsnake = snakenode;
}

void PrintSnake(snake* p2)
{
	node* p = NULL;
	int i;
	i = colorflow;
	p = p2->snake;
	while (p != NULL)
	{
		while (i == 7 || i == 8)
			i++;
		setpos(p->x, p->y);
		Color(i);
		printf(SNAKE);
		if (i < 15)
			i++;
		else
			i = 1;
		p = p->next;
	}
	if (colorflow < 15)
		colorflow++;
	else
		colorflow = 1;
	Color(16);
	setpos(0, 38);
}

void SnakeDirChange(snake* p2)
{
	node* next;
	next = (node*)malloc(sizeof(node));
	next->prev = NULL;
	next->next = NULL;
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
	if (hasfood(p2, next))
	{
		score += 3;
		setpos(94, 13);
		printf("    ");
		setpos(94, 13);
		Color(14);
		printf("%d", score);
		Color(16);
		eatfood(p2, next);
	}
	else if (hasweeds(p2, next))
	{
		score -= 3;
		setpos(94, 13);
		printf("    ");
		setpos(94, 13);
		Color(14);
		printf("%d", score);
		Color(16);
		eatweeds(p2);
	}
	else if (hasboom(p2, next))
	{
		if (score > 0 && nodeofsnake > 5)
			score -= ((nodeofsnake - 5) / 2) * 3;
		else
			score -= nodeofsnake / 2;
		setpos(94, 13);
		printf("    ");
		setpos(94, 13);
		Color(14);
		printf("%d", score);
		Color(16);
		touchboom(p2);
	}
	else if (HasWall(next->x, next->y))
	{
		killbywallflag = 1;
		dirflag = p2->dir;
		times = 1;
	}
	//else if (HasSnakeSelf(next->x, next->y))
	//{
	//	p2->status = SelfKill;
	//}
	else if (HasDoor(next) && score >= 100)
		EnterDoor(p2);
	else
		nofood(p2, next);
}

void SnakeRun(snake* p2)
{
	while (p2->status == Ready)
	{
		if (GetAsyncKeyState(VK_UP) && p2->dir != DOWN)
			p2->dir = UP;
		if (GetAsyncKeyState(VK_DOWN) && p2->dir != UP)
			p2->dir = DOWN;
		if (GetAsyncKeyState(VK_LEFT) && p2->dir != RIGHT)
			p2->dir = LEFT;
		if (GetAsyncKeyState(VK_RIGHT) && p2->dir != LEFT)
			p2->dir = RIGHT;
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			PrintWindows(11, PAUSE);
			Color(11);
			setpos(40, 20);
			printf("游戏暂停！");
			setpos(38, 22);
			printf("按F1键继续游戏");
			setpos(37, 24);
			printf("按F3键保存并退出");
			Color(16);
			setpos(0, 50);
			while (1)
			{
				if (GetAsyncKeyState(VK_F1))
					break;
				if (GetAsyncKeyState(VK_F3))
				{
					SaveGame(p2);
					p2->status = Save;
					break;
				}
			}
			system("cls");
			PrintMap(Chapter);
			PrintScoreTable();
			PrintFood(p2);
			PrintWeeds(p2);
			PrintBoom(p2);
			PrintIllustratedHandbook();
		}
		if (GetAsyncKeyState(VK_CONTROL) && p2->staytime >= 75)
			p2->staytime -= 25;
		if (GetAsyncKeyState(VK_MENU) && p2->staytime <= 200)
			p2->staytime += 25;
		SnakeDirChange(p2);
		PrintSnake(p2);
		Sleep(p2->staytime);
		WeedBlink(p2);
		PrintProcessBar();
		if (score >= 100)
		{
			Color(14);
			PrintDoor();
		}
		RePrintBoom(p2);
		if (NotPrintFood(p2->food->x,p2->food->y))
			PrintFood(p2);
		GameOver(p2);
		setpos(0, 50);
	}
}

int HasSnakeSelf(int x,int y)
{
	char ch[3];
	ch[0] = GetStr(x, y, 1);
	ch[1] = GetStr(x, y, 2);
	ch[2] = '\0';
	if (!strcmp(ch, SNAKE))
		return 1;
	else
		return 0;
}