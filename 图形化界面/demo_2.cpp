#include<graphics.h>
#include<conio.h>
#include<time.h>


void show();
void startup();
void updateWithInput();
void updateWithoutInput();
void gameover();

//初始化球
int High = 480, Width = 640;
float  ball_x, ball_y;
float ball_vx, ball_vy;
float radius;
//初始化挡板
int bar_x, bar_y;
int bar_high, bar_width;
int bar_left, bar_right, bar_top, bar_bottom;
//砖块
#define Brick_num 10  //砖块个数
int isBrickExisted[Brick_num];
int brick_high, brick_width;


void startup()
{
	ball_x = Width / 2;
	ball_y = High / 2;
	ball_vx = 2;
	ball_vy = 2;
	radius = 20;

	bar_high = High / 20;
	bar_width = Width / 5;
	bar_x = Width / 5;
	bar_y = High - bar_high / 2;
	bar_left = bar_x - bar_width / 2;
	bar_right = bar_x + bar_width / 2;
	bar_top = bar_y - bar_high / 2;
	bar_bottom = bar_y + bar_high / 2;

	brick_width = Width / Brick_num;
	brick_high = High / Brick_num;
	for (int i = 0; i < Brick_num; i++)
		isBrickExisted[i] = 1;

	srand(time(NULL));
	initgraph(Width, High);
	HWND hnd = GetHWnd();
	SetWindowText(hnd,_T("消砖块"));
	BeginBatchDraw();//用于批量绘图  执行之后任何绘图操作都不会输出 指导执行道FlushBAtchDraw he EndBatchDraw

}
void show()
{

	setfillcolor(RED);
	fillcircle(ball_x, ball_y, radius);

	setfillcolor(WHITE);
	bar(bar_left, bar_top, bar_right, bar_bottom);

	int brick_left, brick_right, brick_bottom, brick_top;
	for (int i = 0; i < Brick_num; i++)
	{
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_high;

		if (isBrickExisted[i])
		{
			setfillcolor(RED);
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
		}
	}
	FlushBatchDraw();
	Sleep(3);
}

void updateWithoutInput()
{
	//坐标更新
	ball_x += ball_vx;
	ball_y += ball_vy;
	//碰撞检测_墙壁
	if ((ball_x <= radius) || ball_x >= Width - radius)
	{
		ball_vx = -ball_vx;
	}
	if (ball_y <= radius)
	{
		ball_vy = -ball_vy;
	}
	if ( ball_y >= High - radius)
	{
		ball_x = rand() % Width;
		ball_y = rand() % High;
	}
	//碰撞检测_挡板
	if (((ball_y + radius >= bar_top) && (ball_y + radius < bar_bottom - bar_high / 3))
		|| ((ball_y - radius <= bar_bottom) && (ball_y - radius > bar_top - bar_high / 3)))
		if ((ball_x >= bar_left) && ball_x <= bar_right)
		{
			ball_vy = -ball_vy;
		}
	int brick_left, brick_right,brick_bottom;
	//碰撞检测_砖块
	for (int i = 0; i < Brick_num; i++)
	{
		if (isBrickExisted[i])
		{
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_bottom = brick_high;
			if ((ball_y == brick_bottom + radius) && (ball_x >= brick_left) && (ball_x < brick_right))
			{
				isBrickExisted[i] = 0;
				ball_vy = -ball_vy;
			}

		}
	}
	//加速
	/*if (score % 5 == 1)
	{
		ball_vx += 1;
		ball_vy += 1;
	}*/
}

void updateWithInput()
{
	char input;
	if (_kbhit())		//w判断是否有输入
	{
		input = _getch();
		if (input == 'a' && bar_left > 0)
		{
			bar_x -= 30;
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
		if (input == 'd' && bar_right < Width)
		{
			bar_x += 30;
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
	}
}

void gameover()
{
	EndBatchDraw();				//用于结束批量绘制并执行未完成的绘制任务
	closegraph();
}

int main()
{
	startup();

	while (1)
	{
		cleardevice();
		updateWithoutInput();
		updateWithInput();
		show();
	}

	gameover();
	return 0;
}