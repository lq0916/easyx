#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<math.h>

#define WIDTH 1024 
#define HEIGHT 768 
#define NUM_MOVERS 800 //С�������
#define FRICTION 0.96f//Ħ����������ϵ��

//����С��ṹ
struct Mover
{
	COLORREF color;//��ɫ
	float x, y;//����
	float vX, vY;//�ٶ�
	float radius;//�뾶
};

//����ȫ�ֱ���
struct Mover movers[NUM_MOVERS];//С������
int mouseX, mouseY;//��ǰ�������
int prevMouseX, prevMouseY;//�ϴ��������
int mouseVX, mouseVY;//�����ٶ�
int isMouseDown;//�������Ƿ���

void startup()
{
	//�����������
	srand((unsigned int)time(NULL));

	//��ʼ��С������
	for (int i = 0; i < NUM_MOVERS; i++)
	{
		movers[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		movers[i].x = rand() % WIDTH;
		movers[i].y = rand() % HEIGHT;
		movers[i].vX = float(cos(float(i))) * (rand() % 34);
		movers[i].vY = float(sin(float(i))) * (rand() % 34);
		movers[i].radius = (rand() % 34) / 15.0;
	}
	//��ʼ����ǰ����ڻ�������
	mouseX = WIDTH / 2;
	mouseY = HEIGHT / 2;
	isMouseDown = 0;//��ʼ���δ����
	initgraph(WIDTH, HEIGHT);
	HWND h = GetHWnd();
	SetWindowText(h, _T("���滥������"));
	BeginBatchDraw();
}

void show()
{
	int i;
	cleardevice();
	for (i = 0; i < NUM_MOVERS; i++)
	{
		//��С��
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
	float avgVX, avgVY, avgV, sc;//����
	float toDist = WIDTH * 0.36;//�������룬��С�������ľ����ڴ˷�Χ����������ڵ�����
	float blowDist = WIDTH * 0.25;//������룬С�������ľ����ڴη�Χ�ڻ��ܵ�����ĳ���
	float stirDist = WIDTH * 0.125;//�Ŷ�����,С���������ڴ˷�Χ�ڻ��ܵ������Ŷ�
	float d;//��ǰС������λ�õľ���
	float dX, dY;//����С��ǰλ�õĲ� 

	//ǰ���������м�����ƶ��ľ��룬�������ٶ�
	mouseVX = mouseX - prevMouseX;
	mouseVY = mouseY - prevMouseY;
	//Ϊ��¼����������꣬�����ϴ�����������
	prevMouseX = mouseX;
	prevMouseY = mouseY;

	for (i = 0; i < NUM_MOVERS; i++)
	{
		x = movers[i].x;//��ǰС�������
		y = movers[i].y;
		vX = movers[i].vX;//��ǰС����ٶ�
		vY = movers[i].vY;

		dX = x - mouseX;//����С��ǰλ�õĲ�  
		dY = y - mouseY;
		d = sqrt(dX * dX + dY * dY);//��ǰС������λ�õľ���

		//���潫dX,dY��һ��������ӳ���򣬺;����޹�
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
		//С��������<toDist,�ٴη�Χ��С����ܵ���������
		if (d < toDist)
		{
			//����������ļ��ٶȷ��ȣ�С��������Խ������ļ��ٶ�Խ��
			//����������ֵ���Ա����������ֵС�ܶ�
			float toAcc = (1 - (d / toDist)) * WIDTH * 0.0014f;
			//��dX,dY��һ��������Ϣ�����ٶȷ���ֵΪtoAcc,�õ��µ�С��߶�
			vX = vX - dX * toAcc;
			vY = vY - dY * toAcc;
		}
		//�����������£�����С��������<blowDist(�ڻ���Χ��)ʱ���ܵ�����ĳ���
		if (isMouseDown && d < blowDist)
		{
			//����������ļ��ٶȷ��ȣ������ʽ��ʾС��������Խ�������������ļ��ٶ�Խ��
			float blowAcc = (1 - (d / blowDist)) * 10;
			//������õ���dX,dY��һ��������Ϣ������ļ��ٶȷ���ֵΪblowAcc,�õ��µ�С���ٶ�
			//float(rand())/RAND_MAX����0~1�������
			//0.5f-float(rand())/RAND_MAX����-0.5~0.5�������������һЩ�Ŷ�
			vX = vX + dX * blowAcc + 0.5f - float(rand()) / RAND_MAX;
			vY = vY + dY * blowAcc + 0.5f - float(rand()) / RAND_MAX;
		}
		//��С��������<stirDist,�ڴ˷�Χ��С����ܵ������Ŷ�
		if (d < stirDist)
		{
			//�Ŷ�������ļ��ٶȷ��ȣ�С��������Խ������ļ��ٶ�Խ���Ŷ�����ֵ��С
			float mAcc = (1 - (d / stirDist)) * WIDTH * 0.00026f;
			//����ٶ�Խ��������Ŷ���Խ��
			vX = vX + mouseVX * mAcc;
			vY = vY + mouseVY * mAcc;
		}

		//С���˶���һ������(Ħ����),�ٶ��𽥼�С
		vX = vX * FRICTION;
		vY = vY * FRICTION;

		//�ٶȵľ���ֵ
		avgVX = fabs(vX);
		avgVY = fabs(vY);
		//���������ٶȵ�ƽ��
		avgV = (avgVX + avgVY) * 0.5f;

		//��Ϊ��������������ã�����ٶȹ�С������һ��0~3���������
		//���ԱȽϴ�ĸ������ٶȱ��
		if (avgVX < 0.1)
			vX = vX * float(rand()) / RAND_MAX * 3;
		if (avgVY < 0.1)
			vY = vY * float(rand()) / RAND_MAX * 3;
		//С��İ뾶��0.4~3.5֮�䣬�ٶ�Խ�󣬰뾶Խ��
		sc = avgV * 0.45f;
		sc = max(min(sc, 3.5f), 0.4f);
		movers[i].radius = sc;
		//���ݡ�λ��+�ٶȡ�����С�������
		nextX = x + vX;
		nextY = y + vY;

		//���С�򳬹��ϡ��¡�����4���߽磬��λ����Ϊ�߽紦���ٶȷ���
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
		//����С��λ��
		movers[i].vX = vX;
		movers[i].vY = vY;
		movers[i].x = nextX;
		movers[i].y = nextY;
	}
}

void updateWithInput()
{
	MOUSEMSG m;//���������Ϣ
	while (MouseHit())//��⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();//�������ƶ������µ�ǰ����������
		if (m.uMsg == WM_MOUSEMOVE)//�������ƶ������µ�ǰ����������
		{
			mouseX = m.x;
			mouseY = m.y;
		}
		else if (m.uMsg == WM_LBUTTONDOWN)//����������
			isMouseDown = 1;
		else if (m.uMsg == WM_LBUTTONUP)//������̧��
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
	startup();//���ݵĳ�ʼ��
	while (1)
	{
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ���
	}
	gameover();//��Ϸ���������к�������
	return 0;
}
