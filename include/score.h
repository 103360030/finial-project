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
		printf("\n�|�L�O���ά����ɿ�!");
		SetColor(15);
	}
	else
	{
		SetColor(10);
		printf("\n����      �m�W        �B��\n");
		printf("--------------------------\n");
		
		while ((fscanf(stream, "%s %s %d", WorL, name, &step)) != EOF)
			printf("%-10s %-8s %5d\n", WorL, name,step);
		SetColor(15);
		fclose(stream);
	}

	printf("\n");

	printf("\n1.��^�D���\n");
	printf("2.���}�C��\n");
	printf("3.�R������!\n");
	do
	{
		do
		{
			ensure = 'y';
			printf("�п�ܥ\��: ");
			scanf("%d", &menu);
			if (menu == 3)
			{
				printf("�T�{�M�����?(Y/N)");
				scanf(" %c", &ensure);
			}
		} while (ensure != 'y' && ensure != 'Y');
	} while (menu != 1 && menu != 2 && menu != 3);
	return menu;
}