#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

//ȫ�ֱ���
int high, width;			//��Ϸ�����С
int ball_x, ball_y;			//С�������
int ball_vx, ball_vy;		//С����ٶ�
int position_x, position_y;	//�������������
int ridus;					//����뾶��С
int left, right;			//���������λ��
int ball_number;			//����С�����
int block_x, block_y;		//ש���λ��
int score;					//������ש�����



//����Ƶ�(X,Y)λ��
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //�ڶ���ֵΪ0����ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup()
{
	high = 15;
	width = 20;
	ball_x = 0;
	ball_y = width / 2;
	ball_vx = 1;
	ball_vy = 1;
	ridus = 5;
	position_x = high;
	position_y = width / 2;
	left = position_y - ridus;
	right = position_y + ridus;
	ball_number = 0;
	block_x = 0;
	block_y = width / 2-1;
	score = 0;
}

//��ʾ����
void show()
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i <= high+1; i++)
	{
		for (j = 0; j <= width; j++)
		{
			if (i == ball_x && j == ball_y)
				printf("O");		//���С��
			else if (j == width)
				printf("|");		//����ұ߿�
			else if (i == high + 1)
				printf("_");		//����±߿�
			else if (i == high && j >= left && j <= right)
				printf("*");		//�������
			else if (i == block_x && j == block_y)
				printf("B");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("����С������%d\n", ball_number);
	printf("������ש������%d\n",score);
}

//���û������޹صĸ���
void updateWithoutInput()
{
	if (ball_x == high - 1)			
	{
		if (ball_y >= left && ball_y <= right)	//û�б����嵲ס
		{
			ball_number++;			//������1
			printf("\a");			//����
			ball_y = ball_y + rand() % 4 - 2;
		}
		else
		{
			printf("��Ϸʧ��\n");
			system("pause");
			exit(0);
		}
	}
	if (ball_x == block_x && ball_y == block_y)
	{
		score++;
		block_y = rand() % width;		//�����µ�ש��
	}
	ball_x += ball_vx;
	ball_y += ball_vy;

	if (ball_x == 0 || ball_x == high - 1)
		ball_vx = -ball_vx;
	if (ball_y == 0 || ball_y == width - 1)
		ball_vy = -ball_vy;
	Sleep(80);
}

//���û������йصĸ���
void updateWithInput()
{
	char input;
	if (_kbhit())		//�ж��Ƿ�������
	{
		input = _getch();
		if (input == 'a'&&left>1)
		{
			position_y--;			//λ������
			left = position_y - ridus;
			right = position_y + ridus;
		}
		if (input == 'd'&&right<width-1)			//λ������
		{
			position_y++;
			left = position_y - ridus;
			right = position_y + ridus;
		}
		
	}

}

int main11()
{
	HideCursor();
	startup();
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	return 0;
}