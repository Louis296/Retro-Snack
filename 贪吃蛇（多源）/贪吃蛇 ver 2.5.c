#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

#define SNAKE "□"
#define WALL "■"
#define SCORETABLE "■"
#define FOOD "●"
#define WINDOW "※"
#define WELCOME "※"
#define WEEDS "§"
#define BOOM "♂"

/*
Ver 2.5 版本特性：
解决地雷的内存释放问题
完善继续游戏窗口
改善数据结构，加入了尾指针
*/

char name[100];
int score, k, snakeskin, nodeofsnake, time1, time2, boomflag;
score = 0, k = 1, nodeofsnake = 0, time1 = 0, time2 = 0;

enum SnakeDir
{
	UP, DOWN, RIGHT, LEFT
};

enum SnakeStatus
{
	Ready,WallKill,SelfKill,WeedsKill,BoomKill
};

enum WindowFormat
{
	END,PAUSE,READY
};

typedef struct node node;
struct node
{
	node* prev;
	int x;
	int y;
	node* next;
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

snake* CreateSnake()
{
	node *head, *p, *p1;
	head = (node*)malloc(sizeof(node));
	head->prev = NULL;
	head->x = 60;
	head->y = 10;
	p = head;
	int i;
	for (i = 1; i < 5; i++)
	{
		p1 = (node*)malloc(sizeof(node));
		p1->prev = p;
		p->next = p1;
		p1->x = p->x + 2;
		p1->y = p->y;
		p1->next = NULL;
		p = p1;
	}
	snake *p2;
	p2 = (snake*)malloc(sizeof(snake));
	p2->snake = head;
	p2->dir = LEFT;
	p2->status = Ready;
	p2->tail = p1;
	nodeofsnake = 5;
    return p2;
}

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

void CreateFood(snake* p2)
{
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL);
	p = (node*)malloc(sizeof(node));
	p2->food = (node*)malloc(sizeof(node));
	p1 = p2->snake;
	flag = 1;
	while (flag||p->y==5||p->y==37||p->x==10||p->x==74)
	{
		srand(seed);
		while (1)
		{
			p->x = rand() % 64 + 10;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % 32 + 5;//随机生成坐标
		while (p1 != NULL)
		{
			if (p1->x != p->x&&p1->y != p->y)
			{
				p1= p1->next;
			}
			else
				break;
		}
		if (p1 == NULL)
		{
			flag = 0;
			seed = (unsigned)time(NULL);
		}
		else
			seed = (unsigned)time(NULL)+10;
	}
	p2->food->x = p->x;
	p2->food->y = p->y;
}

void CreateWeeds(snake* p2)
{
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL)+1000;
	p = (node*)malloc(sizeof(node));
	p2->weeds = (node*)malloc(sizeof(node));
	p1 = p2->snake;
	flag = 1;
	while (flag || p->y == 5 || p->y == 37 || p->x == 10 || p->x == 74)
	{
		srand(seed);
		while (1)
		{
			p->x = rand() % 64 + 10;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % 32 + 5;//随机生成坐标
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
			seed = (unsigned)time(NULL)+1000;
		}
		else
			seed = (unsigned)time(NULL) + 10000;
		if (p->x == p2->food->x&&p->y == p2->food->y)
			flag = 1;
	}
	p2->weeds->x = p->x;
	p2->weeds->y = p->y;
}

void CreateBoom(snake* p2)
{
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL) + 10000;
	p = (node*)malloc(sizeof(node));
	p2->boom = (node*)malloc(sizeof(node));
	p1 = p2->snake;
	flag = 1;
	while (flag || p->y == 5 || p->y == 37 || p->x == 10 || p->x == 74)
	{
		srand(seed);
		while (1)
		{
			p->x = rand() % 64 + 10;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % 32 + 5;//随机生成坐标
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
			seed = (unsigned)time(NULL) + 10000;
		}
		else
			seed = (unsigned)time(NULL) + 100000;
		if (p->x == p2->food->x&&p->y == p2->food->y)
			flag = 1;
		if (p->x == p2->weeds->x&&p->y == p2->weeds->y)
			flag = 1;
	}
	p2->boom->x = p->x;
	p2->boom->y = p->y;
}

void PrintSnake(snake* p2, int mode)
{
	node* p = NULL;
	int i;
	i = k;
	p = p2->snake;
	switch (mode)
	{
	case 1://七彩虚幻蛇
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
		if (k < 15)
			k++;
		else
			k = 1;
	}
	Color(16);
	setpos(0, 38);
}

void PrintFood(snake* p2)
{
	setpos(p2->food->x, p2->food->y);
	Color(10);
	printf(FOOD);
	Color(16);
}

void PrintWeeds(snake* p2)
{
	setpos(p2->weeds->x, p2->weeds->y);
	Color(4);
	printf(WEEDS);
	Color(16);
}

void PrintBoom(snake* p2)
{
	setpos(p2->boom->x, p2->boom->y);
	Color(15);
	printf(BOOM);
	Color(16);
}

void PrintMap()
{
	int i;
	Color(6);
	for (i = 10; i <= 74; i+=2)
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
	Color(16);
}
                                                                                                                                                                                                                                                                                                                                                                               
void PrintWelcome()
{
	Color(11);
	int i;
	for (i = 10; i <= 110; i += 2)
	{
		setpos(i, 5);
		printf(WELCOME);
		setpos(i, 37);
		printf(WELCOME);
	}
	for (i = 6; i <= 36; i++)
	{
		setpos(10, i);
		printf(WELCOME);
		setpos(110, i);
		printf(WELCOME);

	}
	Color(16);
}

void PrintWindows(int color, int mode)
{
	Color(color);
	int i;
	switch (mode)
	{
	case END:
		for (i = 32; i <= 56; i += 2)
		{
			setpos(i, 18);
			printf(WINDOW);
			setpos(i, 26);
			printf(WINDOW);
		}
		for (i = 19; i <= 25; i++)
		{
			setpos(32, i);
			printf(WINDOW);
			setpos(56, i);
			printf(WINDOW);
		}
		break;
	case PAUSE:
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
	}
	Color(16);
}

int hasfood(snake* p2, node* next)
{
	if (next->x == p2->food->x&&next->y == p2->food->y)
		return 1;
	else
		return 0;
}

int hasweeds(snake* p2, node* next)
{
	if (next->x == p2->weeds->x&&next->y == p2->weeds->y)
		return 1;
	else
		return 0;
}

int hasboom(snake* p2, node* next)
{
	if (p2->boom->x == next->x&&p2->boom->y == next->y)
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
}

void eatweeds(snake* p2, node* next)
{
	node *p1;
	p1 = p2->tail;
	p2->tail = p2->tail->prev;
	setpos(p1->x, p1->y);
	printf(" ");
	setpos(p2->weeds->x, p2->weeds->y);
	printf(" ");
	if (p1->prev != NULL)
	{
		p1->prev->next = NULL;
		free(p1);
		CreateWeeds(p2);
		PrintWeeds(p2);
	}
	nodeofsnake--;
}

void touchboom(snake* p2)
{
	int i;
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
		setpos(p2->boom->x, p2->boom->y);
		printf(" ");
		CreateBoom(p2);
		PrintBoom(p2);
	}
	if (nodeofsnake == 1)
	{
		boomflag = 1;
		nodeofsnake = 0;
	}
	nodeofsnake -= nodeofsnake / 2;
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
		eatweeds(p2, next);
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
	else
		nofood(p2, next);
}

int killbywall(snake* p2)
{
	if (p2->snake->y == 5 || p2->snake->y == 37 || p2->snake->x == 10 || p2->snake->x == 74)
		return 1;
	else
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
		setpos(34, 24);
		printf("按F1重新开始，ESC退出");
		Color(16);
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
		setpos(34, 24);
		printf("按F1重新开始，ESC退出");
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
		setpos(34, 24);
		printf("按F1重新开始，ESC退出");
		Color(16);

	}
}

void PrintTips()
{
	setpos(88, 17);
	printf("操作指南：");
	setpos(92, 19);
	printf("ESC--暂停");
	setpos(92, 21);
	printf("↑--向上称动");
	setpos(92, 23);
	printf("↓--向下移动");
	setpos(92, 25);
	printf("←--向左移动");
	setpos(92, 27);
	printf("→--向右移动");
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
			setpos(37, 22);
			printf("按回车键继续游戏");
			Color(16);
			setpos(0, 38);
			getchar();
			system("cls");
			PrintMap();
			PrintScoreTable();
			PrintFood(p2);
			PrintWeeds(p2);
			PrintBoom(p2);
			PrintIllustratedHandbook();
		}
		SnakeDirChange(p2);
		PrintSnake(p2,snakeskin);
		GameOver(p2);
		Sleep(p2->staytime);
		time1++;
		time2++;
		if (time1 >= 10 && time1 <= 15)
		{
			setpos(p2->weeds->x, p2->weeds->y);
			printf(" ");
		}
		if (time1 >= 20)
		{
			PrintWeeds(p2);
			time1 = 0;
		}
		if (time2 >= 80)
		{
			setpos(p2->weeds->x, p2->weeds->y);
			printf(" ");
			CreateWeeds(p2);
			PrintWeeds(p2);
			time2 = 0;
		}
		setpos(0, 50);
	} 
}

void SelectLevel()
{

}

void InputName()
{
	setpos(54, 15);
	fgets(name, 100, stdin);
}

void WelcomePlayer1()
{
	PrintWelcome();
	Color(3);
	setpos(47, 10);
	printf("欢迎来到贪吃蛇 Ver 2.5 版本");
	setpos(53, 13);
	printf("请输入玩家姓名：");
	setpos(50, 25);
	printf("按回车确认并进入游戏");
	Color(14);
	setpos(88, 35);
	printf("Created by Louis296");
	InputName();
	Color(16);
	setpos(0, 38);
}

void WelcomePlayer2()
{
	PrintWelcome();
	Color(3);
	setpos(14, 7);
	printf("欢迎玩家");
	Color(14);
	printf(" %s", name);
	Color(3);
	setpos(55, 10);
	printf("贪 吃 蛇");
	Color(14);
	setpos(100, 33);
	printf("Ver 2.5");
	setpos(88, 35);
	printf("Created by Louis296");

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

int main(void)
{
	system("mode con cols=130 lines=55");
	snake *p2;
	snakeskin = 1;
	WelcomePlayer1();
	system("cls");
	WelcomePlayer2();
	getchar();
	system("cls");
	PrintMap();
	PrintScoreTable();
	PrintIllustratedHandbook();
	ReadyWindow();
	getchar();
  l:system("cls");
    PrintMap();
	PrintScoreTable();
	PrintIllustratedHandbook();
	p2 = CreateSnake();
	p2->staytime = 100;
	CreateFood(p2);
	CreateWeeds(p2);
	CreateBoom(p2);
	PrintSnake(p2, snakeskin);
	PrintFood(p2);
	PrintWeeds(p2);
	PrintBoom(p2);
	SnakeDirChange(p2);
	SnakeRun(p2);
	system("pause");
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
			goto l;
		}
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
}

