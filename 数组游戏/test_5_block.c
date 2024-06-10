#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define High 30
#define Width 40		//游戏画面尺寸

//全局变量
int ball_x, ball_y;					//小球的坐标
int ball_vx, ball_vy;				//小球的速度
int canvas[High][Width] = { 0 };	//二维数组储存游戏画布对应的元素0为空格，1为小球
int position_x, position_y;			//挡板的中心坐标
int ridus;							//挡板的半径大小
int left, right;					//挡板的左右位置
int score;							//得分


// 光标移到(X, Y)位置
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
		canvas[position_x][k] = 2;			//加挡板
	for (k = 0; k < Width; k++)
		for (i = 0; i < High / 4; i++)
			canvas[i][k] = 3;
}

//显示画面
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
	printf("得分：%d\n", score);
	Sleep(2);
}

//与用户无关的更新
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
			printf("游戏失败\n");
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
	//更新小球坐标
	
	//边界反弹
	if (ball_x == 0 || ball_x == High - 2)		//由此处避免erro:95
		ball_vx = -ball_vx;
	if (ball_y == 0 || ball_y == Width - 1)
		ball_vy = -ball_vy;
	
	//砖块反弹
	if (canvas[ball_x - 1][ball_y] == 3)
	{
		ball_vx = -ball_vx;
		canvas[ball_x - 1][ball_y] = 0;
		
		printf("\a");
		score++;
	}
	}
}

//与用户输入有关的数据更新
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
			canvas[position_x][left] = 2;			//此处更改左边挡板的数组元素值

		}
		if (input == 'd' && right < Width - 1)
		{
			canvas[position_x][left] = 0;
			position_y++;
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;			//此处更改左边挡板的数组元素值

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