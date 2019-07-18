#include<stdio.h>
#include<windows.h>
#include<io.h>
#include"Snake.h"

extern char name[100];
extern int score;
extern int nodeofsnake;
extern int Chapter;
extern int initx, inity;

void SaveGame(snake* p2)
{
	FILE* fp;
	node* p;
	if (access("Save", 0) != 0)
		fp = fopen("Save", "w+");
	else
		fp = fopen("Save", "w");
	fprintf(fp, "%d,%s\r", score, name);
	fprintf(fp, "%d,%d\r", nodeofsnake, Chapter);
	fprintf(fp, "%d,%d\r", p2->food->x, p2->food->y);
	p = p2->boom;
	do
	{
		fprintf(fp, "%d,%d\r", p->x, p->y);
		p = p->next;
	} while (p != NULL);
	p = p2->weeds;
	do
	{
		fprintf(fp, "%d,%d\r", p->x, p->y);
		p = p->next;
	} while (p != NULL);
	p = p2->snake;
	int i;
	for (i = 1; i <= nodeofsnake; i++)
	{
		fprintf(fp, "%d,%d\r", p->x, p->y);
		p = p->next;
	}
	fprintf(fp, "%d,%d", p2->dir, p2->staytime);
	fclose(fp);
}

int ReadSave(snake* p2)
{
	FILE* fp;
	if (access("Save", 0) != 0)
	{
		PrintWindows(12, WARNNING);
		Color(12);
		setpos(58, 21);
		printf("´íÎó£¡");
		setpos(56, 23);
		printf("ÎÞ ´æ µµ£¡");
		Color(16);
		setpos(0, 50);
		system("pause");
		return 0;
	}
	else
	{
		p2->food = (node*)malloc(sizeof(node));
		fp = fopen("Save", "r");
		fscanf(fp, "%d,%s", &score, name);
		fscanf(fp, "%d,%d", &nodeofsnake, &Chapter);
		fscanf(fp, "%d,%d", &p2->food->x, &p2->food->y);
		node* p;
		int i;
		CreateBoom(p2, Chapter);
		p = p2->boom;
		for (i = 1; i <= Chapter; i++)
		{
			fscanf(fp, "%d,%d", &p->x, &p->y);
			p = p->next;
		}
		CreateWeeds(p2, Chapter);
		p = p2->weeds;
		for (i = 1; i <= Chapter; i++)
		{
			fscanf(fp, "%d,%d", &p->x, &p->y);
			p = p->next;
		}
		fscanf(fp, "%d,%d", &initx, &inity);
		CreateSnake(p2, nodeofsnake, initx, inity);
		p = p2->snake;
		p = p->next;
		for (i = 1; i < nodeofsnake; i++)
		{
			fscanf(fp, "%d,%d", &p->x, &p->y);
			p = p->next;
		}
		fscanf(fp, "%d,%d", &p2->dir, &p2->staytime);
		return 1;
	}
	fclose(fp);
}