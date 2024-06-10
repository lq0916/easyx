#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

//全局变量
int high, width;			//游戏画面大小
int ball_x, ball_y;			//小球的坐标
int ball_vx, ball_vy;		//小球的速度
int position_x, position_y;	//挡板的中心坐标
int ridus;					//挡板半径大小
int left, right;			//挡板的左右位置
int ball_number;			//反弹小球次数
int block_x, block_y;		//砖块的位置
int score;					//消掉的砖块个数



//光标移到(X,Y)位置
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //第二个值为0，表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//数据初始化
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

//显示画面
void show()
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i <= high+1; i++)
	{
		for (j = 0; j <= width; j++)
		{
			if (i == ball_x && j == ball_y)
				printf("O");		//输出小球
			else if (j == width)
				printf("|");		//输出右边框
			else if (i == high + 1)
				printf("_");		//输出下边框
			else if (i == high && j >= left && j <= right)
				printf("*");		//输出挡板
			else if (i == block_x && j == block_y)
				printf("B");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("反弹小球数：%d\n", ball_number);
	printf("消掉的砖块数：%d\n",score);
}

//与用户输入无关的更新
void updateWithoutInput()
{
	if (ball_x == high - 1)			
	{
		if (ball_y >= left && ball_y <= right)	//没有被挡板挡住
		{
			ball_number++;			//次数加1
			printf("\a");			//响铃
			ball_y = ball_y + rand() % 4 - 2;
		}
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (ball_x == block_x && ball_y == block_y)
	{
		score++;
		block_y = rand() % width;		//产生新的砖块
	}
	ball_x += ball_vx;
	ball_y += ball_vy;

	if (ball_x == 0 || ball_x == high - 1)
		ball_vx = -ball_vx;
	if (ball_y == 0 || ball_y == width - 1)
		ball_vy = -ball_vy;
	Sleep(80);
}

//与用户输入有关的更新
void updateWithInput()
{
	char input;
	if (_kbhit())		//判断是否有输入
	{
		input = _getch();
		if (input == 'a'&&left>1)
		{
			position_y--;			//位置左移
			left = position_y - ridus;
			right = position_y + ridus;
		}
		if (input == 'd'&&right<width-1)			//位置右移
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