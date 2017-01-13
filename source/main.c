#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "game.h"
#include "score.h"

void wipeout(void);

void main(void)
{
	int choice;
	int i;
	do
	{
		SetColor(15);
		system("cls");
		printf("    主菜單   \n");
		printf("-------------\n");
		printf("1.踩地雷\n");
		printf("2.歷史紀錄\n");
		printf("3.離開遊戲\n");
		printf("請輸入功能: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			minesweeper();
			break;
		case 2:
			i = score();
			if (i == 2)
			{
				choice = 3;
			}
			else if (i == 3)
			{
				wipeout();
			}
			break;
		case 3:
			break;
		default:
			SetColor(12);
			printf("輸入錯誤!請重新輸入!\n");
			SetColor(15);
			system("pause");
			break;
		}
	} while (choice != 3);
}

void wipeout()
{
	remove("score.txt");	
}