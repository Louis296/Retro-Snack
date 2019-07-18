#include<stdio.h>
#include"Snake.h"

extern int score;
extern char name[100];

void PrintMap(int Chapter)
{
	int i, j;
	Color(6);
	setpos(12, 3);
	printf("Chapter.%d", Chapter);
	for (i = 10; i <= 74; i += 2)
	{
		setpos(i, 5);
		printf(WALL);
		setpos(i, 37);
		printf(WALL);
	}
	for (i = 6; i <= 36; i++)
	{
		setpos(10, i);
		printf(WALL);
		setpos(74, i);
		printf(WALL);
	}
	if (Chapter == 2)
	{
		for (i = 17; i <= 25; i++)
		{
			setpos(42, i);
			printf(WALL);
		}
	}
	if (Chapter == 3)
	{
		for (i = 17; i <= 25; i++)
		{
			setpos(42, i);
			printf(WALL);
		}
		for (i = 34; i <= 50; i+=2)
		{
			setpos(i, 21);
			printf(WALL);
		}
	}
	if (Chapter == 4)
	{
		for (i = 17; i <= 25; i++)
		{
			setpos(42, i);
			printf(WALL);
		}
		for (i = 34; i <= 50; i += 2)
		{
			setpos(i, 21);
			printf(WALL);
		}
		j = 10;
		for (i = 16; i <= 20; i += 2)
		{
			setpos(i, j--);
			printf(WALL);
		}
		j = 10;
		for (i = 68; i >= 64; i -= 2)
		{
			setpos(i, j--);
			printf(WALL);
		}
		j = 32;
		for (i = 16; i <= 20; i += 2)
		{
			setpos(i, j++);
			printf(WALL);
		}
		j = 32;
		for (i = 68; i >= 64; i -= 2)
		{
			setpos(i, j++);
			printf(WALL);
		}
		
	}
	Color(16);
}

void PrintWindows(int color,enum WindowsFormat mode)
{
	Color(color);
	int i;
	switch (mode)
	{
	case END:
		for (i = 29; i <= 59; i += 2)
		{
			setpos(i, 18);
			printf(WINDOW);
			setpos(i, 26);
			printf(WINDOW);
		}
		for (i = 19; i <= 25; i++)
		{
			setpos(29, i);
			printf(WINDOW);
			setpos(59, i);
			printf(WINDOW);
		}
		break;
	case PAUSE:
		for (i = 34; i <= 54; i += 2)
		{
			setpos(i, 18);
			printf(WINDOW);
			setpos(i, 26);
			printf(WINDOW);
		}
		for (i = 19; i <= 25; i++)
		{
			setpos(34, i);
			printf(WINDOW);
			setpos(54, i);
			printf(WINDOW);
		}
		break;
	case READY:
		for (i = 34; i <= 54; i += 2)
		{
			setpos(i, 18);
			printf(WINDOW);
			setpos(i, 24);
			printf(WINDOW);
		}
		for (i = 19; i <= 23; i++)
		{
			setpos(34, i);
			printf(WINDOW);
			setpos(54, i);
			printf(WINDOW);
		}
		break;
	case WARNNING:
		for (i = 50; i <= 70; i += 2)
		{
			setpos(i, 19);
			printf(WINDOW);
			setpos(i, 25);
			printf(WINDOW);
		}
		for (i = 20; i <= 24; i++)
		{
			setpos(50, i);
			printf(WINDOW);
			setpos(70, i);
			printf(WINDOW);
		}
	}
	Color(16);
}

void PrintTips()
{
	setpos(88, 17);
	printf("操作指南：");
	setpos(92, 19);
	printf("ESC--暂停");
	setpos(92, 21);
	printf("↑--向上移动");
	setpos(92, 23);
	printf("↓--向下移动");
	setpos(92, 25);
	printf("←--向左移动");
	setpos(92, 27);
	printf("→--向右移动");
	setpos(92, 29);
	printf("CTRL--蛇加速");
	setpos(92, 31);
	printf("ALT--蛇减速");
}

void PrintProcessBar()
{
	Color(13);
	int flag,i;
	flag = 58 + (score / 4) * 2;
	for (i = 58; i <= flag; i = i + 2)
	{
		if (i >= 60 && i <= 108)
		{
			setpos(i, 41);
			printf(WALL);
			setpos(i, 42);
			printf(WALL);
			setpos(i, 43);
			printf(WALL);
		}
	}
}

void ClearProcessBar()
{
	int i;
	for (i = 60; i <= 108; i+=2)
	{
		setpos(i, 41);
		printf("  ");
		setpos(i, 42);
		printf("  ");
		setpos(i, 43);
		printf("  ");
	}
}

void PrintScoreTable()
{
	Color(11);
	int i;
	for (i = 80; i <= 110; i += 2)
	{
		setpos(i, 5);
		printf(SCORETABLE);
		setpos(i, 37);
		printf(SCORETABLE);
	}
	for (i = 6; i <= 36; i++)
	{
		setpos(80, i);
		printf(SCORETABLE);
		setpos(110, i);
		printf(SCORETABLE);
	}
	setpos(88, 9);
	printf("玩家：");
	Color(14);
	printf("%s", name);
	setpos(88, 12);
	Color(11);
	printf("得分：");
	setpos(94, 13);
	Color(14);
	printf("%d", score);
	Color(11);
	PrintTips();
	Color(16);
}

void PrintIllustratedHandbook()
{
	int i;
	Color(11);
	for (i = 10; i <= 110; i += 2)
	{
		setpos(i, 40);
		printf(WALL);
		setpos(i, 48);
		printf(WALL);
	}
	for (i = 41; i <= 47; i++)
	{
		setpos(10, i);
		printf(WALL);
		setpos(110, i);
		printf(WALL);
	}
	for (i = 41; i <= 47; i++)
	{
		setpos(58, i);
		printf(WALL);
	}
	for (i = 60; i <= 110; i += 2)
	{
		setpos(i, 44);
		printf(WALL);
	}
	Color(14);
	setpos(62, 46);
	printf("当上方能量条集满时，通往下一关的传送门就会打开");
	Color(10);
	setpos(14, 42);
	printf(FOOD);
	Color(14);
	printf(" --食物");
	Color(4);
	setpos(14, 44);
	printf(WEEDS);
	Color(14);
	printf(" --毒草");
	Color(15);
	setpos(14, 46);
	printf(BOOM);
	Color(14);
	printf(" --地雷");
	setpos(32, 44);
	printf(DOOR);
	printf(" --传送门");
}

void ReadyWindow()
{
	PrintWindows(11, READY);
	Color(11);
	setpos(40, 20);
	printf("准备游戏！");
	setpos(37, 22);
	printf("按回车键开始游戏");
	Color(16);
}
