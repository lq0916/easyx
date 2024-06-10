#include"game.h"


//全局变量
#define High 20
#define Width 30

int canvas[High][Width] = { 0 };
int food_x, food_y;					//0为空格  -1为边框# 1表示蛇头@ 大于1表示蛇身* -2为食物 
int moveDirection;		//小蛇的移动方向    上下左右1234
int score;			//得分
//移动小蛇
// 第一步扫描数组canvas的多有元素  找到正数元素+1；
// 找到最大的元素值，将其 变为0    //蛇尾消失
// 找到为2的元素  蛇头一局输入 将对应方向的的像素值加一
void moveSnakeByDirection()
{
	int i, j;
	for(i=1;i<High-1;i++)
		for (j = 1; j < Width-1; j++)
		{
			if (canvas[i][j] > 0)
				canvas[i][j]++;
		}
	int oldTail_i, oldTail_j, oldHead_i, oldHead_j;
	int max=0;

	for(i=1;i<High-1;i++)
		for(j=1;j<Width-1;j++)
			if (canvas[i][j] > 0)
			{
				if (max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_i = i;
					oldTail_j = j;
				}
				if (canvas[i][j] == 2)
				{
					oldHead_i = i;
					oldHead_j = j;
				}
			}

	int newHead_i, newHead_j;

	if (moveDirection == 1)//上移动
	{
		newHead_i = oldHead_i - 1;
		newHead_j = oldHead_j;
	}
	if (moveDirection == 2)//下移动
	{
		newHead_i = oldHead_i + 1;
		newHead_j = oldHead_j;
	}
	if (moveDirection == 3)//左移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j-1;
	}
	if (moveDirection == 4)//右移动
	{
		newHead_i = oldHead_i;
		newHead_j = oldHead_j + 1;
	}
	//如果蛇头吃到食物
	if (canvas[newHead_i][newHead_j] == -2)
	{
		score++;
		canvas[food_x][food_y] = 0;
		//产生一个新的食物
		food_x = rand() % (High - 5) + 2;
		food_y = rand() % (Width - 5) + 2;
		canvas[food_x][food_y] = -2;
	}
	else
		canvas[oldTail_i][oldTail_j] = 0;

	//判断🐍是否与自身或边框相撞
	if (canvas[newHead_i][newHead_j] > 0 || canvas[newHead_i][newHead_j] == -1)
	{
		printf("游戏失败\n");
		Sleep(2000);
		system("pause");
		exit(0);
	}
	else
		canvas[newHead_i][newHead_j] = 1;
}

//初始化数据
void startup()
{
	int i, j;
	//初始化边框
	for (i = 0; i < High; i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width - 1] = -1;
	}
	for (j = 0; j < Width; j++)
	{
		canvas[0][j] = -1;
		canvas[High - 1][j] = -1;
	}
	//初始化蛇头
	canvas[High / 2][Width / 2] = 1;
	//初始化🐍身体，画布中元素为23456
	for (i = 1; i <= 4; i++)
		canvas[High/2][Width / 2 - i] = i + 1;
	//初始化🐍右移
	moveDirection = 4;
	//初始化食物
	food_x = rand() % (High - 5) + 2;
	food_y = rand() % (Width - 5) + 2;
	canvas[food_x][food_y] = -2;

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
				printf(" ");		//输出空格
			else if (canvas[i][j] == -1)
				printf("#");		//输出边框
			else if (canvas[i][j] == 1)
				printf("@");		//输出蛇头
			else if (canvas[i][j] > 1)
				printf("*");		//输出🐍身
			else if (canvas[i][j] == -2)
				printf("F");
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
	Sleep(100);
}

//输入与用户无关的更新
void updateWithoutInput()
{
	moveSnakeByDirection();
}

//与用户输入有关的更新
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
		if (input == 'a')
		{
			moveDirection = 3;//右移
			moveSnakeByDirection();
		}
		else if (input == 'd')
		{
			moveDirection = 4;//左移
			moveSnakeByDirection();
		}
		else if (input == 'w')
		{
			moveDirection = 1;//上移
			moveSnakeByDirection();
		}
		else if (input == 's')
		{
			moveDirection = 2;//下移
			moveSnakeByDirection();
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
	return 0;
}