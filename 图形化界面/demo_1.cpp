#include<graphics.h>			//应用EasyX库
#include<conio.h>
#include<math.h>
#include <tchar.h> 

//void test1()
//{
//	//绘图函数
//
//	line(x1, y1, x2, y2);		//画出（x1,x2）（x2,y2）两端点的直线
//	circle(x, y, r);			//画圆
//	putpixel(x, y, c);			//画点（x,y）  像素颜色为c
//	solidrectangle(x1, y1, x2, y2);	//矩形 左上角为1  右下角为2
//
//	setlinecolor(c);			//设置线条颜色
//	setfillcolor(c);			//设置填充颜色
//	setbkcolor(c);				//设置背景颜色
//	setcolor(c);				//设置前景颜色
//}

void test2()
{
	//绘制一个圆
	initgraph(640, 640);		//初始化画布640*640
	setcolor(YELLOW);			//设置圆的线条颜色为黄色
	setfillcolor(GREEN);		//设置园内以绿色填充
	fillcircle(100, 100, 20);	//画实心圆  （x,y,r）
	_getch();
	closegraph();				//关闭画布
 }

void test3()
{
	initgraph(640, 480);
	for (int y = 0; y <= 480; y = y + 48)
	{
		//将颜色循环改变
		setlinecolor(RGB(0,0,y));		//RGB三原色 （r,g,b）red green blue 0~255
		line(0, y, 640, y);
	}
	_getch();
	closegraph();
}

void test4()
{
	initgraph(640, 200);
	for (int y = 0; y <= 200; y = y + 5)
	{
		if (y / 5 % 2 == 1)		//判断奇偶
		{
			setlinecolor(RGB(255, 0, 0));
		}
		else
		{
			setlinecolor(RGB(0, 0, 255));
		}
		line(0, y, 640, y);
	}
	_getch();
	closegraph();
}

void test5()
{
	//绘制围棋、
	int step = 30;
	//初始画布
	initgraph(600, 600);
	//背景色
	setbkcolor(YELLOW);
	//用背景色清空屏幕
	cleardevice();

	setlinestyle(PS_SOLID, 2);//画实线 宽度为两个像素
	setcolor(RGB(0, 0, 0));
	int i;
	for (i = 1; i <= 19; i++)
	{
		line(i * step, 1 * step, i * step, 19 * step);
		line(1 * step, i * step, 19 * step, i * step);
	}
	_getch();
	closegraph();
}

void test6()
{
	//绘制国际象棋棋盘

	int step = 50;
	//初始画布
	initgraph(500, 500);
	//背景色
	setbkcolor(YELLOW);
	//用背景色清空屏幕
	cleardevice();
	int i, j;
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if ((i + j )% 2 == 1)
			{
				setfillcolor(BLACK);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);
			}
		}
	}
	_getch();
	closegraph();
}

//简单的动画演示
void fun1()
{
	initgraph(640, 480);
	for (int x = 100; x < 540; x += 20)
	{
		setcolor(YELLOW);
		setfillcolor(WHITE);
		fillcircle(x, 100, 20);
		//延时
		Sleep(200);
		cleardevice();
		/*setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(x, 100, 20);*/
	}
	closegraph();
}
void fun2()
{
	//简单反弹球

	//初始化球
	int High = 480, Width = 640;
	float  ball_x, ball_y;
	float ball_vx, ball_vy;
	float radius;
	
	initgraph(Width, High);
	ball_x = Width / 2;
	ball_y = High / 2;
	ball_vx = 2;
	ball_vy = 2;
	radius = 20;
	while (1)
	{
		cleardevice();
		/*setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(ball_x, ball_y, radius);*/

		//坐标更新
		ball_x += ball_vx;
		ball_y += ball_vy;
		if ((ball_x <= radius) || ball_x >= Width - radius)
		{
			ball_vx = -ball_vx;
		}
		if ((ball_y <= radius) || ball_y >= High - radius)
		{
			ball_vy = -ball_vy;
		}
		//setcolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(ball_x, ball_y, radius);
		
		Sleep(3);
	}
	closegraph();
}
void fun3()
{
	//简单反弹球

	//初始化球
	int High = 480, Width = 640;
	float  ball_x, ball_y;
	float ball_vx, ball_vy;
	float radius;

	initgraph(Width, High);
	ball_x = Width / 2;
	ball_y = High / 2;
	ball_vx = 20;
	ball_vy = 20;
	radius = 20;

	BeginBatchDraw();//用于批量绘图  执行之后任何绘图操作都不会输出 指导执行道FlushBAtchDraw he EndBatchDraw
	while (1)
	{
		cleardevice();
		/*setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(ball_x, ball_y, radius);*/

		//坐标更新
		ball_x += ball_vx;
		ball_y += ball_vy;
		if ((ball_x <= radius) || ball_x >= Width - radius)
		{
			ball_vx = -ball_vx;
		}
		if ((ball_y <= radius) || ball_y >= High - radius)
		{
			ball_vy = -ball_vy;
		}
		//setcolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(ball_x, ball_y, radius);
		FlushBatchDraw();			//用于执行未完成的的绘制任务 执行批量绘制

		Sleep(1);
	}
	EndBatchDraw();				//用于结束批量绘制并执行未完成的绘制任务
	closegraph();
}

void fun4()
{
	//游戏尺寸
	int High = 480, Width = 640;
	//小球数目
	#define BallNum 5
	float minDistances2[BallNum][2];		//[i][1]记录距小球i最近的下标 [i][0]距离平方

	float  ball_x[BallNum], ball_y[BallNum];
	float ball_vx[BallNum], ball_vy[BallNum];
	float radius = 20;
	int i, j;
	//初始化小球
	for (i = 0; i < BallNum; i++)
	{
		ball_x[i] = rand() % int(Width - 4 * radius) + 2 * radius;
		ball_y[i] = rand() % int(High - 4 * radius) + 2 * radius;
		ball_vy[i] = rand()%10*(i+1);
		ball_vx[i] = rand()%10*(i+1);

		minDistances2[i][0] = 9999999;
		minDistances2[i][1] = -1;
	}

	initgraph(Width, High);
	BeginBatchDraw();

	while (1)
	{
		setfillcolor(WHITE);
		for (i = 0; i < BallNum; i++)
		{
			fillcircle(ball_x[i], ball_y[i], radius);
		}
		FlushBatchDraw();
		Sleep(3);

		//墙壁碰撞检测
		for (i = 0; i < BallNum; i++)
		{
			if ((ball_x[i] <= radius) || ball_x[i] >= Width - radius)
			{
				ball_vx[i] = -ball_vx[i];
			}
			if ((ball_y[i] <= radius) || ball_y[i] >= High - radius)
			{
				ball_vy[i] = -ball_vy[i];
			}

		}
		

		//求距离平方
		for (i = 0; i < BallNum; i++)
		{
			for (j = 0; j < BallNum; j++)
			{
				if (i != j)
				{
					float dist2;
					dist2 = (ball_x[i] - ball_x[j]) * (ball_x[i] - ball_x[j])
						+ (ball_y[i] - ball_y[j]) * (ball_y[i] - ball_y[j]);
					if (dist2 < minDistances2[i][0])
					{
						minDistances2[i][0] = dist2;
						minDistances2[i][1] = j;
					}
				}
			}
		}
		//判断小球是否碰撞
		for (i = 0; i < BallNum; i++)
		{
			if (minDistances2[i][0] <= 4 * radius * radius)
			{
				j = minDistances2[i][1];
				
				//swap v
				int temp;
				temp = ball_vx[i]; ball_vx[i] = ball_vx[j]; ball_vx[j] = temp;
				temp = ball_vy[i]; ball_vy[i] = ball_vy[j]; ball_vy[j] = temp;
				
				minDistances2[j][0] = 9999999;
				minDistances2[j][1] = -1;
			}
		}
		//更新小球坐标
		for (i = 0; i < BallNum; i++)
		{
			ball_x[i] += ball_vx[i];
			ball_y[i] += ball_vy[i];

			if (ball_x[i] < radius) ball_x[i] = radius;
			if (ball_y[i] < radius) ball_y[i] = radius;
			if (ball_x[i] > Width - radius) ball_x[i] = Width - radius;
			if (ball_y[i] > High - radius) ball_y[i] = High - radius;
		}
		//清空画布
		cleardevice();
	}
	EndBatchDraw();
	closegraph();
}
void fun5()
{
	#define M_PI 3.14159265358979323846
	int High = 640, Width = 640;
	initgraph(Width, High);
	int center_x = Width / 2;
	int center_y = High / 2;
	SYSTEMTIME ti;

	//秒针
	int secondLength = Width / 7;		//秒针长度
	int secondEnd_x, secondEnd_y;
	float secondAngle;
	//分针
	int minuteLength = Width / 6;
	int minuteEnd_x, minuteEnd_y;
	float minuteAngle;
	//时针
	int hourLength = Width / 5;
	int hourEnd_x, hourEnd_y;
	float hourAngle;

	BeginBatchDraw();
	while(1)
	{
		//绘制表盘
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		//画刻度
		int x, y, i;
		for (i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.3 * sin(M_PI * 2 * i / 60));
			y = center_y + int(Width / 4.3 * cos(M_PI * 2 * i / 60));
			
			if (i % 15 == 0) 
				bar(x - 5, y - 5, x + 5, y + 5);
			else if (i % 5 == 0)	
				circle(x, y, 3);
			else 
				putpixel(x, y, WHITE);
		}
		outtextxy(center_x - 25, center_y + Width / 6, _T("My clock"));

		//获取当前时间
		GetLocalTime(&ti);
		secondAngle = ti.wSecond * 2 * M_PI / 60;
		minuteAngle = ti.wMinute * 2 * M_PI / 60 + secondAngle / 60;
		hourAngle = ti.wHour * 2 * M_PI / 12 + minuteAngle / 12;

		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);

		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);
		//秒针
		setlinestyle(PS_SOLID, 2);//实线 连个像素
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		
		setlinestyle(PS_SOLID, 4);//实线 连个像素
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		setlinestyle(PS_SOLID, 6);//实线 连个像素
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(10);

		cleardevice();
	}
	EndBatchDraw();
	_getch();
	closegraph();

}
int main() 
{
	//test1();		//pass
	//test2();		//pass
	//test3();		//pass
	//test4();		//绘制交错红蓝线
	//test5();		//绘制围棋棋盘
	//test6();		//绘制国际象棋
	//fun1();		//简单动画演示
	//fun2();		//反弹球->出现屏闪
	//fun3();		//使用beginbatchDraw解决屏闪
	//fun4();		//多个反弹球
	fun5();			//实时钟表
	return 0;	
}