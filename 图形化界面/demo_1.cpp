#include<graphics.h>			//Ӧ��EasyX��
#include<conio.h>
#include<math.h>
#include <tchar.h> 

//void test1()
//{
//	//��ͼ����
//
//	line(x1, y1, x2, y2);		//������x1,x2����x2,y2�����˵��ֱ��
//	circle(x, y, r);			//��Բ
//	putpixel(x, y, c);			//���㣨x,y��  ������ɫΪc
//	solidrectangle(x1, y1, x2, y2);	//���� ���Ͻ�Ϊ1  ���½�Ϊ2
//
//	setlinecolor(c);			//����������ɫ
//	setfillcolor(c);			//���������ɫ
//	setbkcolor(c);				//���ñ�����ɫ
//	setcolor(c);				//����ǰ����ɫ
//}

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
	ball_vx = 20;
	ball_vy = 20;
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

void fun4()
{
	//��Ϸ�ߴ�
	int High = 480, Width = 640;
	//С����Ŀ
	#define BallNum 5
	float minDistances2[BallNum][2];		//[i][1]��¼��С��i������±� [i][0]����ƽ��

	float  ball_x[BallNum], ball_y[BallNum];
	float ball_vx[BallNum], ball_vy[BallNum];
	float radius = 20;
	int i, j;
	//��ʼ��С��
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

		//ǽ����ײ���
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
		

		//�����ƽ��
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
		//�ж�С���Ƿ���ײ
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
		//����С������
		for (i = 0; i < BallNum; i++)
		{
			ball_x[i] += ball_vx[i];
			ball_y[i] += ball_vy[i];

			if (ball_x[i] < radius) ball_x[i] = radius;
			if (ball_y[i] < radius) ball_y[i] = radius;
			if (ball_x[i] > Width - radius) ball_x[i] = Width - radius;
			if (ball_y[i] > High - radius) ball_y[i] = High - radius;
		}
		//��ջ���
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

	//����
	int secondLength = Width / 7;		//���볤��
	int secondEnd_x, secondEnd_y;
	float secondAngle;
	//����
	int minuteLength = Width / 6;
	int minuteEnd_x, minuteEnd_y;
	float minuteAngle;
	//ʱ��
	int hourLength = Width / 5;
	int hourEnd_x, hourEnd_y;
	float hourAngle;

	BeginBatchDraw();
	while(1)
	{
		//���Ʊ���
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		//���̶�
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

		//��ȡ��ǰʱ��
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
		//����
		setlinestyle(PS_SOLID, 2);//ʵ�� ��������
		setcolor(WHITE);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		
		setlinestyle(PS_SOLID, 4);//ʵ�� ��������
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		setlinestyle(PS_SOLID, 6);//ʵ�� ��������
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
	//test4();		//���ƽ��������
	//test5();		//����Χ������
	//test6();		//���ƹ�������
	//fun1();		//�򵥶�����ʾ
	//fun2();		//������->��������
	//fun3();		//ʹ��beginbatchDraw�������
	//fun4();		//���������
	fun5();			//ʵʱ�ӱ�
	return 0;	
}