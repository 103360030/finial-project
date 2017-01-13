/*   ** �C���]�p�����G
1. ��a�p��9*9����l�A�@10���a�p
2. ��ܼƦr�����@����񪺤K�Ӧa�Ϧ@���X���a�p
����ܼƦr�h��ܪ��񪺤K�Ӧa�ϨS�a�p

** �{���]�p�����G
1. �N��l�ŧi��int bomps[9][9]���}�C�A�s���T����
0  �N��w�����a�ϡA�B����S�a�p
1~ 8  �N��w�����a�ϡA�����񦳦a�p�A�Ʀr���a�p��
-1  �N��|���Q��쪺�a�p��
10~18  �N��w�Q������w���a��
-2  �N��w�Q��쪺�a�p�ϡA�C������

2. �b�ù��W�L�X��l
3. �ШϥΪ̿�J�Ĥ@�ӭn���}����m(x, y)
2. �Q�ζüƩ�m�a�p�Q���A�b�����ƪ���m�B���O�ϥΪ̿�J����}
4. �b�w���a�ϭp����T(����X���a�p)
5. �N��Q����쪺�w���a�ϭȥ[10(�N��w���)
6. �M���ù�
7. ���bomps�}�C���A��>10����T�]>10�N��w�g����^
8. �ШϥΪ̿�J���U�ӭn���}����m(x2, y2)
9. �p��(x2, y2)���� (�w��-> bomps[x2][y2] += 10�F�a�p-> bomps[x2][y2] = -2�A�C������)
10. �p�Gbomps[x2, y2]���Ȭ�10�A�h���}���񪺮�l
10. �Y�������h����step 6 ~ 9�A����Ĺ(������>10 or ==-1 )�N���X
11. �߰ݬO�_�A���@���A�Y�A���@���h����2~10
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

void assign_initial(int bomps[][11]);                                           //�N��l����T��l�Ƭ�0
void print_blanks(void);                                                        //�L�X�C����l����l 
void open_cell(int *op_x, int *op_y);                                           //�ШϥΪ̿�J�n���}����m
void put_mine(int bomps[][11], int op_x, int op_y);                             //��m�a�p
void calculate_num_of_bomps(int bomps[][11]);                                   //�p��D�a�p�Ϫ��񦳴X���a�p 
void assign_inf_after_open(int bomps[][11], int op_x, int op_y);                //���ܨϥΪ̥��}����m����T
void open_surrounding(int bomps[][11], int p_x, int op_y);                      //���}���񪺰ϰ�]���l����L�a�p�ɡ^ 
void check_no_mine(int bomps[][11], int op_x, int op_y);                        //�ˬd���񪺰ϰ즳�S���a�p 
int  check_over(int bomps[][11], int op_x, int op_y);                           //�ˬd�C���O�_����(���Ĺ)
void print_bomps(int bomps[][11], int op_x, int op_y, int over);                //�L�X�ثe�����p
void print_condition_playing(int bomps[][11]);                                  //�L�X�|�����������p
void print_condition_over(int bomps[][11], int over);                           //�L�X�C�����������p(�C�Ӯ�l����T) 
char play_again(void);                                                          //�߰ݬO�_�A���@��


void SetColor(int ForgC)

{

	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))

	{

		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);

		SetConsoleTextAttribute(hStdOut, wColor);

	}

	return;

}

int minesweeper(void)
{
	int  bomps[11][11],
		open_x, open_y,
		over;
	char again;

	typedef struct _rank
	{
		char name[10];
		int step;
	}rank;
	rank r;

	do {
		r.step = 0;
		system("cls");
		assign_initial(bomps);                                                   //�N��l����T��l�Ƭ�0
		print_blanks();                                                          //�L�X�C����l����l 
		open_cell(&open_x, &open_y);                                             //�ШϥΪ̿�J�n���}����m
		r.step++;
		put_mine(bomps, open_x, open_y);                                         //��m�a�p
		calculate_num_of_bomps(bomps);                                           //�p��D�a�p�Ϫ��񦳴X�u�a�p
		assign_inf_after_open(bomps, open_x, open_y);                            //���ܨϥΪ̥��}����m����T
		check_no_mine(bomps, open_x, open_y);                                    //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
		over = check_over(bomps, open_x, open_y);                                //�ˬd�C���O�_����(���Ĺ)
		print_bomps(bomps, open_x, open_y, over);                                //�L�X�ثe�����p
		while (over == 0)
		{
			open_cell(&open_x, &open_y);
			r.step++;
			assign_inf_after_open(bomps, open_x, open_y);                      //�ШϥΪ̿�J�n���}����m
			check_no_mine(bomps, open_x, open_y);                              //�ˬd���񪺰ϰ즳�S���a�p�A�ñN�L�a�p���ϰ쥴�}
			over = check_over(bomps, open_x, open_y);                          //�ˬd�C���O�_����(���Ĺ)
			print_bomps(bomps, open_x, open_y, over);                          //�L�X�ثe�����p
		}
		printf("\n�A�ϥΤF");
		SetColor(10);
		printf("%d", r.step);
		SetColor(15);
		printf("�B !\n");
		FILE *stream;														   //�����B�ơB�m�W
		stream = fopen("score.txt", "a+");
		if (stream == NULL)
		{
			printf("�������J����!\n");
		}
		else
		{
			printf("\n\n�п�J�m�W:");
			scanf("%s", r.name);
			if (over == 1)
			{
				fprintf(stream, "winner!! %5s   %5d\n", r.name, r.step);
			}
			else
			{
				fprintf(stream, "loser..  %5s   %5d\n", r.name, r.step);
			}
			fclose(stream);
		}

		again = play_again();                       //�߰ݬO�_�A���@��
	} while (again == 'Y' || again == 'y');
	printf("\n");

	return(0);
}

void assign_initial(int bomps[][11]) {                                          //�N��l����T��l�Ƭ�0 
	int i, j;
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 11; j++)
		{
			bomps[i][j] = 0;
		}
	}
}

void print_blanks(void) {                                                       //�L�X�C����l����l 
	int i, j;
	printf("              �C�������G\n");
	printf("---------------------------------------\n");
	SetColor(11);
	printf("�� �n�}�ҳ̥��W������п�J1 1\n");
	printf("   ���U�@��h���䪺��+1(��J�G2 1)\n");
	printf("   ���k�@��h�k�䪺��+1(��J�G1 2)\n");
	printf("   ��l�H�������A�q1 1 ~ 9 9\n");
	printf("   ��J�榡���G�Ʀr�Ů�Ʀr�A�p�G8 2\n\n");
	printf("�� �i�@����J�h��y�СA\n");
	printf("   �y�ж��u�ݥH�D�Ʀr�Ÿ��j�}�N�i�H�F�I\n");
	printf("   ���z�C���r�֡I:)\n");
	SetColor(15);
	printf("---------------------------------------\n\n");
	printf("    ");
	for (i = 1; i <= 9; i++)
	{
		SetColor(14);
		printf("%2d", i);
		SetColor(15);
	}
	printf("\n");
	for (i = 1; i <= 9; i++)
	{
		for (j = 0; j <= 9; j++)
		{
			if (j == 0)
			{
				SetColor(14);
				printf("%4d", i);
				SetColor(15);
			}
			else
			{
				printf("�f");
			}
				
		}
		printf("\n");
	}
}

void open_cell(int *op_x, int *op_y)                                            //�ШϥΪ̿�J�n���}����m
{
	int x, y;
	printf("\n��J�z�n�}�Ҫ��y�� >> ");
	SetColor(14);
	scanf("%d%d", op_x, op_y);
	SetColor(15);
}

void put_mine(int bomps[][11], int op_x, int op_y) 
{                          
	srand(time(NULL));          
	int  n = 0,
		rand_num,
		cell_x,
		cell_y;

	do {
		rand_num = rand() % 81;                                                               // ( rand() % (�̤j��-�̤p��+1)) + �̤p��
		cell_x = (rand_num % 9) + 1;
		cell_y = ((rand_num - cell_x) / 9) + 1;
		if (bomps[cell_x][cell_y] != -1 && !(cell_x == op_x && cell_y == op_y))
		{
			bomps[cell_x][cell_y] = -1;
			n++;
		}
	} while (n < 10);
}

void calculate_num_of_bomps(int bomps[][11]) {                                  //�p��D�a�p�Ϫ��񦳴X�u�a�p 
	int i, j, u, v;
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			if (bomps[i][j] == 0)												//���p�L���O-1(���u)
			{
				for (u = i - 1; u <= i + 1; u++)									//�o���FOR�O�n�䬵�u���P��K�Ӧ�l
				{
					for (v = j - 1; v <= j + 1; v++)
					{
						if (bomps[u][v] == -1)									//�p�G���@���A�h����m���ƭȥ[1
							bomps[i][j]++;
					}
				}
			}
		}
	}
}

void assign_inf_after_open(int bomps[][11], int op_x, int op_y) {               //���ܨϥΪ̥��}����m����T 
	if (bomps[op_x][op_y] == -1)
		bomps[op_x][op_y] = -2;
	if (bomps[op_x][op_y] >= 0 && bomps[op_x][op_y] <= 8)
		bomps[op_x][op_y] += 10;
}
 
void open_surrounding(int bomps[][11], int op_x, int op_y) {                              //���}���񪺰ϰ�]���l����L�a�p�ɡ^ 
	int i, j;
	for (i = op_x - 1; i <= op_x + 1; i++) {
		for (j = op_y - 1; j <= op_y + 1; j++) {
			if (bomps[i][j] >= 0 && bomps[i][j] <= 8 && i % 10 != 0 && j % 10 != 0)      //�����K�Ӥ��]�A��ɼƦr�C(����)
			{
				bomps[i][j] += 10;												         //�[�Q��ܦw���w�}�L
				check_no_mine(bomps, i, j);
			}
		}
	}
}

void check_no_mine(int bomps[][11], int op_x, int op_y) {                       //�ˬd���񪺰ϰ즳�S���a�p
	if (bomps[op_x][op_y] == 10)        //����S�a�p 
		open_surrounding(bomps, op_x, op_y);
}

void print_condition_playing(int bomps[][11]) {                                 //�L�X�|�����������p
	int i, j;
	printf("    ");
	for (i = 1; i <= 9; i++)
	{
		SetColor(14);
		printf("%2d", i);
		SetColor(15);
	}
	printf("\n");
	for (i = 1; i <= 9; i++) {
		for (j = 0; j <= 9; j++) {
			if (j == 0)
			{
				SetColor(14);
				printf("%4d", i);
				SetColor(15);
			}
			else if (bomps[i][j] < 10)
				printf("�f");
			else if (bomps[i][j] == 10)
				printf(" 0");
			else if (bomps[i][j] > 10 && bomps[i][j] <= 18)
				printf(" %d", bomps[i][j] - 10);
		}
		printf("\n");
	}
}


void print_condition_over(int bomps[][11], int over) {                          //�L�X�C�����������p(�C�Ӯ�l����T) 
	int i, j;
	
	printf("  �z�ССССССССТ{\n");

	for (i = 1; i <= 9; i++) {
		for (j = 0; j <= 10; j++) {
			if (j == 0)
			{
				printf("  �U");
			}
			else if (j == 10)
			{
				printf("�U");
			}
			else if (bomps[i][j] % 10 == 0)
				printf("�D");
			else if (bomps[i][j] == -1)
			{
				SetColor(20);
				printf(" *");
				SetColor(15);
			}
			else if (bomps[i][j] == -2)
			{
				SetColor(12);
				printf("��");
				SetColor(15);
			}
			else
				printf("%2d", bomps[i][j] % 10);
		}
		printf("\n");
	}
	printf("  �|�ССССССССТ}\n");
	if (over == 1)
	{
		SetColor(14);
		printf("        ����~�F�`��!\n\n");
		SetColor(15);
	}
	else
	{
		SetColor(14);
		printf("        �z�F~�[��l! \n\n");
		SetColor(15);
	}
	SetColor(20);
	printf(" *");
	SetColor(15);
	printf("�����u !\n");
	SetColor(12);
	printf("��");
	SetColor(15);
	printf("�O���z�����u !\n");
}

void print_bomps(int bomps[][11], int op_x, int op_y, int over) {               //�L�X�ثe�����p
	system("cls");
	printf("\n");
	int i, j;
	if (over == 0) {
		print_condition_playing(bomps);
	}
	else
		print_condition_over(bomps, over);
}

int  check_over(int bomps[][11], int op_x, int op_y) 
{                                                                                //result == 0 ->�|�������Aresult == 1 ->Ĺ�Aresult == -1 ->��
	int i, j, result = 1;
	if (bomps[op_x][op_y] == -2) {
		result = -1;
	}
	else {
		for (i = 1; i <= 9 && result == 1; i++)
		for (j = 1; j <= 9 && result == 1; j++)
		if ((bomps[i][j] >= 0 && bomps[i][j] <= 8))
			result = 0;
	}
	return(result);
}

char play_again(void) {                                                         //�߰ݬO�_�A���@��
	char again;
	printf("\n�٭n�A���@���ܡH");
	do {
		printf("\n�n�A���@�����ܽп�JY�A\n");
		printf("�ο�JN��^�D���C >>");
		scanf(" %c", &again);
	} while (again != 'Y' && again != 'y' && again != 'N' && again != 'n');
	return(again);
}
