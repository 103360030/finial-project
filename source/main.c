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
		printf("    �D���   \n");
		printf("-------------\n");
		printf("1.��a�p\n");
		printf("2.���v����\n");
		printf("3.���}�C��\n");
		printf("�п�J�\��: ");
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
			printf("��J���~!�Э��s��J!\n");
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