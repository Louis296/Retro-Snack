#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<mmsystem.h>
#include"Snake.h"
#pragma comment(lib,"winmm.lib")

/*
Ver 6.0 版本特性：
添加蛇吃到自身会死的设定
添加多个毒草和地雷
取消对于蛇皮肤的选择接口
*/

char name[100];
int score, colorflow,nodeofsnake, time1, time2, boomflag, Chapter, ReadGameFlag;
int initx, inity;
score = 0, colorflow = 1, nodeofsnake = 0, time1 = 0, time2 = 0;
ReadGameFlag = 0;

void setpos(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void Color(short x)
{
	if (x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int HasWall(int x, int y)
{
	char ch[3];
	ch[0] = GetStr(x, y, 1);
	ch[1] = GetStr(x, y, 2);
	ch[2] = '\0';
	if (!strcmp(ch, WALL))
		return 1;
	else
		return 0;
}

void Playbgm()
{
	switch (Chapter)
	{
	case 1:	
		PlaySound(TEXT("Chapter1.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case 2:	
		PlaySound(TEXT("Chapter2.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case 3:	
		PlaySound(TEXT("Chapter3.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	case 4:
		PlaySound(TEXT("Chapter4.wav"), NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
		break;
	}
}

int main(void)
{
	system("mode con cols=130 lines=55");
	snake *p2;
	rank *p;
	p2 = (snake*)malloc(sizeof(snake));
	p = (rank*)malloc(sizeof(rank));
	CreateRankList(p);
	ReadRankList(p);
	ReadAchievement();
	WelcomePlayer1();
start:system("cls");
    if (WelcomePlayer2(p2, p))
	{
		getchar();
		system("cls");
		PrintMap(Chapter);
		PrintScoreTable();
		PrintIllustratedHandbook();
		ReadyWindow();
		getchar();
	restart:system("cls");
		Playbgm();
		PrintMap(Chapter);
		PrintScoreTable();
		PrintIllustratedHandbook();
		if (ReadGameFlag == 0)
		{
			CreateSnake(p2, 5, 56, 10);
			p2->boom = (node*)malloc(sizeof(node));
			p2->boom->x = 0;
			p2->boom->y = 0;    //初始化地雷坐标，防止第一次生成食物时因不存在地雷坐标而报错
			CreateFood(p2);
			CreateWeeds(p2, Chapter);
			CreateBoom(p2, Chapter);
			p2->staytime = 150;
		}
		ReadGameFlag = 0;
		PrintSnake(p2);
		PrintFood(p2);
		PrintWeeds(p2);
		PrintBoom(p2);
		SnakeDirChange(p2);
		SnakeRun(p2);
		p = WriteRankList(p);
		SaveRankList(p);
		SaveAchievement();
		if (p2->status != Save && p2->status != NextChapter)
		{
			system("pause");
			ReadGameFlag = 0;
			while (1)       //防止因误按造成的游戏退出
			{
				if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT))
				{
					setpos(0, 50);
					system("pause");
				}
				if (GetAsyncKeyState(VK_F1))
				{
					score = 0;
					goto restart;
				}
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					score = 0;
					goto start;
				}
			}
		}
		else if (p2->status == NextChapter)
		{
			if (Chapter < 4)
			{
				Chapter++;
				score = 0;
				goto restart;
			}
			else
			{
				PrintWindows(12, READY);
				Color(6);
				setpos(40, 20);
				printf("游戏胜利");
				setpos(37, 22);
				printf("按Esc键返回主界面");
				setpos(0, 50);
				while (1)
					if (GetAsyncKeyState(VK_ESCAPE))
						break;
				goto start;
			}
		}
		else
			goto start;
	}
    return 0;
}