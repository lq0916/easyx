#include<graphics.h>			//Ӧ��EasyX��
#include<conio.h>

int x1, x2, y1, y2, x, y, c, r;

void test1()
{
	//��ͼ����

	line(x1, y1, x2, y2);		//������x1,x2����x2,y2�����˵��ֱ��
	circle(x, y, r);			//��Բ
	putpixel(x, y, c);			//���㣨x,y��  ������ɫΪc
	solidrectangle(x1, y1, x2, y2);	//���� ���Ͻ�Ϊ1  ���½�Ϊ2

	setlinecolor(c);			//����������ɫ
	setfillcolor(c);			//���������ɫ
	setbkcolor(c);				//���ñ�����ɫ
	setcolor(c);				//����ǰ����ɫ
}

void test2()
{
	//����һ��Բ
	initgraph(640, 640);		//��ʼ������640*640
	setcolor(YELLOW);			//����Բ��������ɫΪ��ɫ
	setfillcolor(GREEN);		//����԰������ɫ���
	fillcircle(100, 100, 20);	//��ʵ��Բ  ��x,y,r��
	_getch();
	closegraph();				//�رջ���
 }

void test3()
{
	initgraph(640, 480);
	for (int y = 0; y <= 480; y = y + 48)
	{
		//����ɫѭ���ı�
		setlinecolor(RGB(0,0,y));		//RGB��ԭɫ ��r,g,b��red green blue 0~255
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
		if (y / 5 % 2 == 1)		//�ж���ż
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
	//����Χ�塢
	int step = 30;
	//��ʼ����
	initgraph(600, 600);
	//����ɫ
	setbkcolor(YELLOW);
	//�ñ���ɫ�����Ļ
	cleardevice();

	setlinestyle(PS_SOLID, 2);//��ʵ�� ���Ϊ��������
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
	//���ƹ�����������

	int step = 50;
	//��ʼ����
	initgraph(500, 500);
	//����ɫ
	setbkcolor(YELLOW);
	//�ñ���ɫ�����Ļ
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

//�򵥵Ķ�����ʾ
void fun1()
{
	initgraph(640, 480);
	for (int x = 100; x < 540; x += 20)
	{
		setcolor(YELLOW);
		setfillcolor(WHITE);
		fillcircle(x, 100, 20);
		//��ʱ
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
	//�򵥷�����

	//��ʼ����
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

		//�������
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
	//�򵥷�����

	//��ʼ����
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

	BeginBatchDraw();//����������ͼ  ִ��֮���κλ�ͼ������������� ָ��ִ�е�FlushBAtchDraw he EndBatchDraw
	while (1)
	{
		cleardevice();
		/*setcolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(ball_x, ball_y, radius);*/

		//�������
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
		FlushBatchDraw();			//����ִ��δ��ɵĵĻ������� ִ����������

		Sleep(1);
	}
	EndBatchDraw();				//���ڽ����������Ʋ�ִ��δ��ɵĻ�������
	closegraph();
}
int main() 
{
	//test1();		//pass
	//test2();		//pass
	//test3();		//pass
	//test4();		//���ƽ��������
	//test5();		//����Χ������
	//test6();		//���ƹ�������
	//fun1();		//�򵥶�����ʾ
	//fun2();			//������->��������
	fun3();
	return 0;
}