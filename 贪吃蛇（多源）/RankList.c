#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>
#include"Snake.h"

extern int score;
extern char name[100];

void SaveRankList(rank* p)
{
	FILE *fp;
	rank* p1;
	p1 = p;
	fp = fopen("RankList", "w");
	while (p1 != NULL)
	{
		fprintf(fp, "%d,%s\r", p1->score1, p1->name1);
		p1 = p1->next;
	}
	fclose(fp);
}

void ReadRankList(rank* p)
{
	FILE *fp;
	rank* p1;
	int i;
	p1 = p;
	if (access("RankList", 0) != 0)
	{
		fp = fopen("RankList", "w+");
		for (i = 1; i < 6; i++)
			fprintf(fp, "0,--\r");
		fclose(fp);
	}
	fp = fopen("RankList", "r");
	do
	{
		fscanf(fp, "%d,%s", &p1->score1, &p1->name1);
		p1 = p1->next;
	} while (p1 != NULL);
	fclose(fp);
}

void CreateRankList(rank* p)
{
	rank *p1, *head;
	head = p;
	head->prev = NULL;
	int i;
	for (i = 1; i <= 4; i++)
	{
		p1 = (rank*)malloc(sizeof(rank));
		p1->prev = p;
		p->next = p1;
		p = p1;
	}
	p1->next = NULL;
	p = head;
}

rank* WriteRankList(rank* p)
{
	rank *p1, *p2;
	int flag;
	flag = 0;
	p1 = p;
	p2 = (rank*)malloc(sizeof(rank));
	p2->prev = NULL;
	p2->next = NULL;
	while (p1 != NULL)
	{
		if (score <= p1->score1)
			p1 = p1->next;
		else
			break;
	}
	if (p1 != NULL)
	{
		if (p1->prev == NULL)
		{
			p1->prev = p2;
			p2->next = p1;
			p = p2;
			flag = 1;
		}
		if (flag != 1)
		{
			if (p1->next != NULL)
			{
				p2->prev = p1->prev;
				p1->prev->next = p2;
				p2->next = p1;
				p1->prev = p2;
			}
			else
			{
				p1->prev->next = p2;
				p2->prev = p1->prev;
				p2->next = p1;
				p1->prev = p2;
			}
		}
		p1 = p;
		int i;
		for (i = 1; i < 6; i++)
		{
			p1 = p1->next;
		}
		if (p1 != NULL)
		{
			p1->prev->next = NULL;
			free(p1);
			strcpy(p2->name1, name);
			p2->score1 = score;
		}
	}
	return p;
}

void PrintRankList(rank*p)
{
	rank* p1;
	p1 = p;
	int i;
	i = 1;
	PrintWelcome();
	Color(3);
	setpos(55, 10);
	printf("排 行 榜");
	setpos(40, 12);
	printf("玩 家");
	setpos(70, 12);
	printf("得 分");
	while (p1 != NULL)
	{
		Color(14);
		setpos(40, 12 + 2 * i);
		printf("%s", p1->name1);
		setpos(70, 12 + 2 * i);
		printf("%d", p1->score1);
		Color(3);
		p1 = p1->next;
		i++;
	}
	setpos(55, 12 + 2 * i);
	printf("按ESC退出");
	setpos(0, 50);
}
