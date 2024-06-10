#include<graphics.h>
#include<conio.h>

//绘制一个圆
void test01()
{
	initgraph(640, 480,0);	//初始化640X480的画布
	setcolor(YELLOW);		//圆的的线条为黄色
	setfillcolor(RED);	//园内以绿色填充
	fillcircle(320, 240, 100);	//画圆 圆心（100，100） r=20
	_getch();					//输入人键盘继续
	closegraph();				//关闭画布
}
//画10条平行线
void test02()
{
	initgraph(640, 480);
	setlinecolor(RED);			//设置线条颜色  setcolor()也可以
	for (int y = 0; y <= 480; y = y + 48)
		line(0, y, 640, y);   //画线  参数左右两端点
	_getch();
	closegraph();

}

//画多条颜色渐变的直线
void test03()
{
	initgraph(640, 256);
	for (int y = 0; y < 256; y++)
	{
		setcolor(RGB(0, y, y));
		line(0, y, 640, y);
	}
	_getch();
	closegraph();
}

//实现红蓝交替的直线
void test04()
{
	initgraph(640, 200);
	for (int y = 0; y <= 200; y = y + 5)
	{
		if (y / 5 % 2 == 0)		//判断奇偶行
			setcolor(RGB(255, 0, 0));
		else
			setcolor(RGB(0, 0, 255));
		line(0, y, 640, y);
	}
	_getch();
	closegraph();
}

//绘制围棋棋盘
void test05()
{
	int step = 30;
	//初始绘画窗口
	initgraph(600, 600);
	//设置背景颜色为黄色
	setbkcolor(YELLOW);
	//用背景色清空屏幕
	cleardevice();

	setlinestyle(PS_SOLID, 2);			//画实线  宽度为两个像素
	setcolor(RGB(0, 0, 0));				//设置为黑色

	int i;
	for (i = 1; i <= 19; i++)
	{
		line(i * step, 1 * step, i * step, 19 * step);//绘制横线
		line(1 * step, i * step, 19 * step, i * step);//绘制竖线
	}
	_getch();
	closegraph();
}

//绘制国际象棋
void test06()
{
	int step = 50;
	//绘制画布
	initgraph(500, 500);
	//设置背景颜色为黄色
	setbkcolor(YELLOW);
	//使用背景色清空屏幕
	cleardevice();

	int i, j;
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if ((i + j) % 2 == 1)
			{
				setfillcolor(BLACK);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);//绘制黑色砖块
				//solidrectangle()左端点  右端点
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);//绘制白色砖块
			}
		}
	}
	_getch();
	closegraph();
}

//动画原理

/*绘制新图形--延时--清除旧图形 */

int main()
{
	test06();

	return 0;
}