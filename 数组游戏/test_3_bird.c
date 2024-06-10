#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

//全局变量
int high, width;					//游戏的画面大小
int bird_x, bird_y;					//小鸟的坐标
int barl_y, barl_xDown, barl_xTop;	//障碍物
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

//数据的初始化
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

//显示画面
void show()
{
	gotoxy(0, 0);
	int i, j;

	for (i = 0; i <= high; i++)
	{
		for (j = 0; j <= width; j++)
		{
			if (i == bird_x && j == bird_y)
				printf("@");	//输出小鸟
			else if (i == high)
				printf("-");
			else if (j == width)
				printf("|");
			else if (j == barl_y && (i<barl_xDown || i>barl_xTop))
				printf("*");	//输出障碍物
			else
				printf(" ");	//输出空格
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
}

//与用户无关的输出
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
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (bird_x == high)
	{
		printf("游戏失败\n");
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

///与用户输入有关的更行
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