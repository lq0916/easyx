#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<math.h>

#define WIDTH 1024 
#define HEIGHT 768 
#define NUM_MOVERS 800 //小球的数量
#define FRICTION 0.96f//摩檫力、阻尼系数

//定义小球结构
struct Mover
{
	COLORREF color;//颜色
	float x, y;//坐标
	float vX, vY;//速度
	float radius;//半径
};

//定义全局变量
struct Mover movers[NUM_MOVERS];//小球数组
int mouseX, mouseY;//当前鼠标坐标
int prevMouseX, prevMouseY;//上次鼠标坐标
int mouseVX, mouseVY;//鼠标的速度
int isMouseDown;//鼠标左键是否按下

void startup()
{
	//设置随机种子
	srand((unsigned int)time(NULL));

	//初始化小球数组
	for (int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x = rand() % WIDTH;
		movers[i].y = rand() % HEIGHT;
		movers[i].vX = float(cos(float(i))) * (rand() % 34);
		movers[i].vY = float(sin(float(i))) * (rand() % 34);
		movers[i].radius = (rand() % 34) / 15.0;
	}
	//初始化当前鼠标在画布中心
	mouseX = WIDTH / 2;
	mouseY = HEIGHT / 2;
	isMouseDown = 0;//初始鼠标未按下
	initgraph(WIDTH, HEIGHT);
	HWND h = GetHWnd();
	SetWindowText(h, _T("仿真互动粒子"));
	BeginBatchDraw();
}

void show()
{
	int i;
	cleardevice();
	for (i = 0; i < NUM_MOVERS; i++)
	{
		//画小球
		setcolor(movers[i].color);
		setfillstyle(movers[i].color);
		fillcircle(int(movers[i].x + 0.5), int(movers[i].y + 0.5), int(movers[i].radius + 0.5));
	}
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput()
{
	int i;
	float x, y, vX, vY;
	float nextX, nextY;
	float avgVX, avgVY, avgV, sc;//阻尼
	float toDist = WIDTH * 0.36;//吸引距离，若小球与鼠标的距离在此范围内则会受向内的引力
	float blowDist = WIDTH * 0.25;//击打距离，小球与鼠标的距离在次范围内会受到向外的斥力
	float stirDist = WIDTH * 0.125;//扰动距离,小球距离鼠标在此范围内会受到鼠标的扰动
	float d;//当前小球和鼠标位置的距离
	float dX, dY;//计算小球当前位置的差 

	//前后两次运行间鼠标移动的距离，即鼠标的速度
	mouseVX = mouseX - prevMouseX;
	mouseVY = mouseY - prevMouseY;
	//为记录这次鼠标的坐标，更新上次鼠标坐标变量
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	for (i = 0; i < NUM_MOVERS; i++)
	{
		x = movers[i].x;//当前小球的坐标
		y = movers[i].y;
		vX = movers[i].vX;//当前小球的速度
		vY = movers[i].vY;

		dX = x - mouseX;//计算小球当前位置的差  
		dY = y - mouseY;
		d = sqrt(dX * dX + dY * dY);//当前小球和鼠标位置的距离

		//下面将dX,dY归一化，仅反映方向，和距离无关
		if (d != 0)
		{
			dX = dX / d;
			dY = dY / d;
		}
		else
		{
			dX = 0;
			dY = 0;
		}
		//小球距离鼠标<toDist,再次范围内小球会受到鼠标的吸引
		if (d < toDist)
		{
			//吸引力引起的加速度幅度，小球距离鼠标越近引起的加速度越大
			//但吸引力的值明显比上面斥力的值小很多
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			//由dX,dY归一化方向信息，加速度幅度值为toAcc,得到新的小球高度
			vX = vX - dX * toAcc;
			vY = vY - dY * toAcc;
		}
		//当鼠标左键按下，并且小球距离鼠标<blowDist(在击打范围内)时会受到向外的斥力
		if (isMouseDown && d < blowDist)
		{
			//击打力引起的加速度幅度，这个公式表示小球距离鼠标越近击打斥力引起的加速度越大
			float blowAcc = (1 - (d / blowDist)) * 10;
			//由上面得到的dX,dY归一化方向信息，上面的加速度幅度值为blowAcc,得到新的小球速度
			//float(rand())/RAND_MAX产生0~1的随机数
			//0.5f-float(rand())/RAND_MAX产生-0.5~0.5的随机数，加入一些扰动
			vX = vX + dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY = vY + dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}
		//若小球距离鼠标<stirDist,在此范围内小球会受到鼠标的扰动
		if (d < stirDist)
		{
			//扰动力引起的加速度幅度，小球距离鼠标越近引起的加速度越大，扰动力的值更小
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			//鼠标速度越大，引起的扰动力越大
			vX = vX + mouseVX * mAcc;
			vY = vY + mouseVY * mAcc;
		}

		//小球运动有一个阻尼(摩擦力),速度逐渐减小
		vX = vX * FRICTION;
		vY = vY * FRICTION;

		//速度的绝对值
		avgVX = fabs(vX);
		avgVY = fabs(vY);
		//两个方向速度的平均
		avgV = (avgVX + avgVY) * 0.5f;

		//因为有上面阻尼的作用，如果速度过小，乘以一个0~3的随机数，
		//会以比较大的概率让速度变大
		if (avgVX < 0.1)
			vX = vX * float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1)
			vY = vY * float(rand()) / RAND_MAX * 3;
		//小球的半径在0.4~3.5之间，速度越大，半径越大
		sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		movers[i].radius = sc;
		//根据“位置+速度”更新小球的坐标
		nextX = x + vX;
		nextY = y + vY;

		//如果小球超过上、下、左、右4个边界，将位置设为边界处，速度反向
		if (nextX > WIDTH)
		{
			nextX = WIDTH;
			vX = -vX;
		}
		else if (nextX < 0)
		{
			nextX = 0;
			vX = -vX;
		}
		if (nextY > HEIGHT)
		{
			nextY = HEIGHT;
			vY = -vY;
		}
		else if (nextY < 0)
		{
			nextY = 0;
			vY = -vY;
		}
		//更新小球位置
		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x = nextX;
		movers[i].y = nextY;
	}
}

void updateWithInput()
{
	MOUSEMSG m;//定义鼠标消息
	while (MouseHit())//检测当前是否有鼠标消息
	{
		m = GetMouseMsg();//如果鼠标移动，更新当前鼠标坐标变量
		if (m.uMsg == WM_MOUSEMOVE)//如果鼠标移动，更新当前鼠标坐标变量
		{
			mouseX = m.x;
			mouseY = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键按下
			isMouseDown = 1;
		else if (m.uMsg == WM_LBUTTONUP)//鼠标左键抬起
			isMouseDown = 0;
	}
}

void gameover()
{
	EndBatchDraw();
	closegraph();
}

int main()
{
	startup();//数据的初始化
	while (1)
	{
		show();//显示画面
		updateWithoutInput();//与用户输入无关的更新
		updateWithInput();//与用户输入有关的更新
	}
	gameover();//游戏结束，进行后续处理
	return 0;
}
