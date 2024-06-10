#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define High 30
#define Width 40		//��Ϸ����ߴ�

//ȫ�ֱ���
int ball_x, ball_y;					//С�������
int ball_vx, ball_vy;				//С����ٶ�
int canvas[High][Width] = { 0 };	//��ά���鴢����Ϸ������Ӧ��Ԫ��0Ϊ�ո�1ΪС��
int position_x, position_y;			//�������������
int ridus;							//����İ뾶��С
int left, right;					//���������λ��
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

//���ݳ�ʼ��
void startup()
{
	ball_x = High / 4;
	ball_y = Width / 2;
	ball_vx = 1;
	ball_vy = 1;
	canvas[ball_x][ball_y] = 1;

	ridus = 5;
	position_x = High - 1;
	position_y = Width / 2;
	left = position_y - ridus;
	right = position_y + ridus;
	score = 0;

	int k,i;
	for (k = left; k <= right; k++)
		canvas[position_x][k] = 2;			//�ӵ���
	for (k = 0; k < Width; k++)
		for (i = 0; i < High / 4; i++)
			canvas[i][k] = 3;
}

//��ʾ����
void show()
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (canvas[i][j] == 0)
				printf(" ");
			else if (canvas[i][j] == 1)
				printf("O");
			else if (canvas[i][j] == 2)
				printf("*");
			else if (canvas[i][j] == 3)
				printf("#");

		}
		printf("|\n");
	}
	for (j = 0; j < Width; j++)
		printf("-");
	printf("\n");
	printf("�÷֣�%d\n", score);
	Sleep(2);
}

//���û��޹صĸ���
void updateWithoutInput()
{
	if (ball_x == High - 2)
	{
		if (ball_y >= left && ball_y <= right)
		{
			  printf("\a");
		}
		else
		{
			printf("��Ϸʧ��\n");
			system("pause");
			exit(0);
		}
	}
	static int speed = 0;
	if (speed < 7)
		speed++;
	if (speed == 7)
	{
		speed = 0;
	

	canvas[ball_x][ball_y] = 0;			
	ball_x += ball_vx;
	ball_y += ball_vy;
	canvas[ball_x][ball_y] = 1;
	//����С������
	
	//�߽練��
	if (ball_x == 0 || ball_x == High - 2)		//�ɴ˴�����erro:95
		ball_vx = -ball_vx;
	if (ball_y == 0 || ball_y == Width - 1)
		ball_vy = -ball_vy;
	
	//ש�鷴��
	if (canvas[ball_x - 1][ball_y] == 3)
	{
		ball_vx = -ball_vx;
		canvas[ball_x - 1][ball_y] = 0;
		
		printf("\a");
		score++;
	}
	}
}

//���û������йص����ݸ���
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'a' && left > 0)
		{
			canvas[position_x][right] = 0;
			position_y--;
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][left] = 2;			//�˴�������ߵ��������Ԫ��ֵ

		}
		if (input == 'd' && right < Width - 1)
		{
			canvas[position_x][left] = 0;
			position_y++;
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;			//�˴�������ߵ��������Ԫ��ֵ

		}

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
}