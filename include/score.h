#include <stdio.h>
#include <stdlib.h>

int score(void)
{
	system("cls");
	char WorL[10];
	char name[10];
	int step;
	int menu;
	char ensure;

	FILE *stream;
	stream = fopen("score.txt", "r");
	if (stream == NULL)
	{
		SetColor(12);
		printf("\n尚無記錄或紀錄檔遺失!");
		SetColor(15);
	}
	else
	{
		SetColor(10);
		printf("\n分類      姓名        步數\n");
		printf("--------------------------\n");
		
		while ((fscanf(stream, "%s %s %d", WorL, name, &step)) != EOF)
			printf("%-10s %-8s %5d\n", WorL, name,step);
		SetColor(15);
		fclose(stream);
	}

	printf("\n");

	printf("\n1.返回主菜單\n");
	printf("2.離開遊戲\n");
	printf("3.刪除紀錄!\n");
	do
	{
		do
		{
			ensure = 'y';
			printf("請選擇功能: ");
			scanf("%d", &menu);
			if (menu == 3)
			{
				printf("確認清除資料?(Y/N)");
				scanf(" %c", &ensure);
			}
		} while (ensure != 'y' && ensure != 'Y');
	} while (menu != 1 && menu != 2 && menu != 3);
	return menu;
}