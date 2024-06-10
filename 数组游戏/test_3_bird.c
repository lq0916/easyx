#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

//ȫ�ֱ���
int high, width;					//��Ϸ�Ļ����С
int bird_x, bird_y;					//С�������
int barl_y, barl_xDown, barl_xTop;	//�ϰ���
int score;							//�÷�

// ����Ƶ�(X, Y)λ��
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

//���ݵĳ�ʼ��
void startup()
{
	high = 15;
	width = 20;
	bird_x = 0;
	bird_y = width / 3;
	barl_y = width ;
	barl_xDown = high / 3;
	barl_xTop = width / 3;
	score = 0;
}

//��ʾ����
void show()
{
	gotoxy(0, 0);
	int i, j;

	for (i = 0; i <= high; i++)
	{
		for (j = 0; j <= width; j++)
		{
			if (i == bird_x && j == bird_y)
				printf("@");	//���С��
			else if (i == high)
				printf("-");
			else if (j == width)
				printf("|");
			else if (j == barl_y && (i<barl_xDown || i>barl_xTop))
				printf("*");	//����ϰ���
			else
				printf(" ");	//����ո�
		}
		printf("\n");
	}
	printf("�÷֣�%d\n", score);
}

//���û��޹ص����
void updateWithoutInput()
{
	bird_x++;
	barl_y--;
	if (bird_y == barl_y)
	{
		if (bird_x >= barl_xDown && bird_x <= barl_xTop)
			score++;
		else
		{
			printf("��Ϸʧ��\n");
			system("pause");
			exit(0);
		}
	}
	if (bird_x == high)
	{
		printf("��Ϸʧ��\n");
		system("pause");
		exit(0);
	}
	if (barl_y <= 0)
	{
		barl_y = width;
		int temp = rand() % (int)(high * 0.8);
		barl_xDown = temp - high / 10;
		barl_xTop = temp + high / 10;
	}
	Sleep(150);
}

///���û������йصĸ���
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (bird_x > 1 && input == ' ')
			bird_x = bird_x - 2;
	}
}

int main()
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