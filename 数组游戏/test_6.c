#include"game.h"

//全局变量
#define High 25
#define Width 50			//游戏画面尺寸
#define EnemyNum 5			//敌机数量

int position_x, position_y;		//飞机的位置 坐标
int canvas[High][Width] = { 0 };		//画布数组
int enemy_x[EnemyNum], enemy_y[EnemyNum];			//敌机的位置

int score;				
int BulletWidth;			//子弹宽度
int EnemyMoveSpeed;			//敌机的移动速度

//数据的初始化
void startup()
{
	position_x = High - 1;
	position_y = Width / 2;
	canvas[position_x][position_y] = 1;
	int k;
	for (k = 0; k < EnemyNum; k++)
	{
		enemy_x[k] = rand() % 2;
		enemy_y[k] = rand() % Width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}
	score = 0;
	BulletWidth = 0;
	EnemyMoveSpeed = 20;

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
				printf(" ");			//输出空格
			else if (canvas[i][j] == 1)
				printf("*");			//输出飞机
			else if (canvas[i][j] == 2)
				printf("|");			//输出子弹
			else if (canvas[i][j] == 3)
				printf("@");			//输出敌机
		}
		printf("\n");
	}
	printf("得分：%3d\n", score);
	Sleep(20);
}

//与用户输出无关的更新
void updateWithoutInput()
{
	int i, j, k;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (canvas[i][j] == 2)	
			{
				for (k = 0; k < EnemyNum; k++)
				{
				if (i == enemy_x[k] & j == enemy_y[k])
				{
					score++;			//得分加1
					printf("\a");
					if (score % 5 == 0 && EnemyMoveSpeed > 3)		//达到一定积分敌机变换
						EnemyMoveSpeed--;
					if (score % 5 == 0)//达到一定分数子弹变得厉害
						BulletWidth++;
					canvas[enemy_x[k]][enemy_y[k]] == 0;
					enemy_x[k] = 0;
					enemy_y[k] = rand() % Width;		//产生新的飞机
					canvas[enemy_x[k]][enemy_y[k]] = 3;
					canvas[i][j] = 0;		//子弹消失
				}
				}
				//子弹上移
				canvas[i][j] = 0;
				if (i > 0)
					canvas[i - 1][j] = 2;
			}
		}
	}
	static int speed = 0;
	if (speed <EnemyMoveSpeed)
	{
		speed++;
	}
	for (k = 0; k < EnemyNum; k++)
	{
		if (position_x == enemy_x[k] && position_y == enemy_y[k])//敌机与飞机相撞
		{
			printf("游戏失败！\n");
			printf("\a\a\a");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		if (enemy_x[k] > High)
		{
			score--;
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0;
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		if (speed == EnemyMoveSpeed)
		{
			for (k = 0; k < EnemyNum; k++)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0;
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}
}

//与用户输出有关的更新
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
			if (input == 'a'&& position_y>0)
			{
				canvas[position_x][position_y] = 0;
				position_y--;			//位置左移
				canvas[position_x][position_y] = 1;
			}
			else if (input == 'd'&& position_y<Width)
			{
				canvas[position_x][position_y] = 0;
				position_y++;			//位置右移
				canvas[position_x][position_y] = 1;
			}
			else if (input == 'w'&& position_x>1)
			{
				canvas[position_x][position_y] = 0;
				position_x--;			//位置上移
				canvas[position_x][position_y] = 1;
			}
			else if (input == 's'&& position_x<High-1)
			{
				canvas[position_x][position_y] = 0;
				position_x++;			//位置下移
				canvas[position_x][position_y] = 1;
			}
			else if (input = ' ')
			{
				int left = position_y - BulletWidth;
				int right = position_y + BulletWidth;
				if (left < 0)
					left = 0;
				if (right > Width - 1)
					right = Width - 1;
				int k;
				for(k=left;k<=right;k++)
				canvas[position_x-1][k] = 2;
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