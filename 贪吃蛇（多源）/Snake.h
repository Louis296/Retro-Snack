#pragma once
#ifndef _SNAKE_H_
#define _SNAKE_H_

#define SNAKE "¡õ"
#define WALL "¡ö"
#define SCORETABLE "¡ö"
#define FOOD "¡ñ"
#define WINDOW "¡ù"
#define WELCOME "¡ù"
#define WEEDS "¡ì"
#define BOOM "¡á"
#define DOOR "…d"

#pragma warning(disable:4996)

enum SnakeDir
{
	UP, DOWN, RIGHT, LEFT, NONE
};

enum SnakeStatus
{
	Ready, WallKill, SelfKill, WeedsKill, BoomKill, Save, NextChapter
};

enum WindowFormat
{
	END, PAUSE, READY, WARNNING
};

typedef struct node node;
struct node
{
	node* prev;
	int x;
	int y;
	node* next;
};

typedef struct rank rank;
struct rank
{
	rank* prev;
	char name1[100];
	int score1;
	rank* next;
};

typedef struct snake
{
	node* snake;
	node* tail;
	node* food;
	node* weeds;
	node* boom;
	enum SnakeDir dir;
	enum SnakeStatus status;
	int staytime;
}snake;

void Color(short x);

void ClearProcessBar();

void CreateBoom(snake* p2,int number);

void CreateFood(snake* p2);

void CreateRankList(rank* p);

void CreateSnake(snake* p2, int snakenode,int x, int y);

void CreateWeeds(snake* p2, int number);

void eatfood(snake* p2, node* next);

void eatweeds(snake* p2);

void EnterDoor(snake* p2);

void GameOver(snake* p2);

char GetStr(int x, int y, int station);

int hasboom(snake* p2, node* next);

int HasDoor(node* next);

int hasfood(snake* p2, node* next);

int HasSnakeSelf(int x, int y);

int HasWall(int x, int y);

int hasweeds(snake* p2, node* next);

void InputName();

int killbyboom(snake* p2);

int killbywall(snake* p2);

int killbyweed(snake* p2);

void nofood(snake* p2, node* next);

int NotPrintFood(int x, int y);

void PrintAchievement();

void PrintBoom(snake* p2);

void PrintFood(snake* p2);

void PrintDoor();

void PrintIllustratedHandbook();

void PrintMap(int Chapter);

void PrintProcessBar();

void PrintRankList(rank* p);

void PrintScoreTable();

void PrintSnake(snake* p2);

void PrintTips();

void PrintWeeds(snake* p2);

void PrintWelcome();

void PrintWindows(int color,enum WindowsFormat mode);

void Playbgm();

void ReadAchievement();

void RePrintBoom(snake* p2);

void ReadRankList(rank* p);

int ReadSave(snake* p2);

void ReadyWindow();

void SaveAchievement();

void SaveRankList(rank* p);

void SaveGame(snake* p2);

void setpos(int x, int y);

void SnakeDirChange(snake* p2);

void SnakeRun(snake* p2);

void touchboom(snake* p2);

void WeedBlink(snake* p2);

void WelcomePlayer1();

int WelcomePlayer2(snake* p2,rank* p);

int WelcomePlayer2_2(snake* p2);

rank* WriteRankList(rank* p);

#endif