#include<stdio.h>
#include<stdlib.h>
#include<io.h>
#include"Snake.h"

int a[10];

void PrintAchievement()
{
	PrintWelcome();
	Color(3);
	setpos(57, 10);
	printf("成   就");
	setpos(44, 12);
	printf("已经达成的成就会以绿色展示");
	setpos(44, 14);
	printf("未达成的成就会以红色展示");
	setpos(40, 18);
	Color(a[0]);
	printf("爆破专家(连吃五个炸弹且存活)");
	setpos(40, 20);
	Color(a[1]);
	printf("药神(连吃十个毒草且存活)");
	setpos(40, 22);
	Color(a[2]);
	printf("无与伦比的传说(开局不吃食物就死)");
	setpos(55, 26);
	Color(3);
	printf("按ESC退出");
	setpos(0, 50);
}

void SaveAchievement()
{
	FILE *fp;
	int i;
	fp = fopen("Achievement", "w");
	for (i = 0; i < 10; i++)
		fprintf(fp, "%d\r", a[i]);
	fclose(fp);
}

void ReadAchievement()
{
	FILE *fp;
	int i;
	if (access("Achievement", 0) != 0)
	{
		fp = fopen("Achievement", "w+");
		for (i = 0; i < 10; i++)
			fprintf(fp, "12\r");
		fclose(fp);
	}
	fp = fopen("Achievement", "r");
	for (i = 0; i < 10; i++)
		fscanf(fp,"%d", &a[i]);
	fclose(fp);
}
