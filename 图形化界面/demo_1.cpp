#include<graphics.h>			//应用EasyX库
#include<conio.h>

int x1, x2, y1, y2, x, y, c, r;

void test1()
{
	//绘图函数

	line(x1, y1, x2, y2);		//画出（x1,x2）（x2,y2）两端点的直线
	circle(x, y, r);			//画圆
	putpixel(x, y, c);			//画点（x,y）  像素颜色为c
	solidrectangle(x1, y1, x2, y2);	//矩形 左上角为1  右下角为2

	setlinecolor(c);			//设置线条颜色
	setfillcolor(c);			//设置填充颜色
	setbkcolor(c);				//设置背景颜色
	setcolor(c);				//设置前景颜色
}

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
	ball_vx = 2;
	ball_vy = 2;
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
int main() 
{
	//test1();		//pass
	//test2();		//pass
	//test3();		//pass
	//test4();		//绘制交错红蓝线
	//test5();		//绘制围棋棋盘
	//test6();		//绘制国际象棋
	//fun1();		//简单动画演示
	//fun2();			//反弹球->出现屏闪
	fun3();
	return 0;
}