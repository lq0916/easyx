#include<graphics.h>
#include<conio.h>

//����һ��Բ
void test01()
{
	initgraph(640, 480,0);	//��ʼ��640X480�Ļ���
	setcolor(YELLOW);		//Բ�ĵ�����Ϊ��ɫ
	setfillcolor(RED);	//԰������ɫ���
	fillcircle(320, 240, 100);	//��Բ Բ�ģ�100��100�� r=20
	_getch();					//�����˼��̼���
	closegraph();				//�رջ���
}
//��10��ƽ����
void test02()
{
	initgraph(640, 480);
	setlinecolor(RED);			//����������ɫ  setcolor()Ҳ����
	for (int y = 0; y <= 480; y = y + 48)
		line(0, y, 640, y);   //����  �����������˵�
	_getch();
	closegraph();

}

//��������ɫ�����ֱ��
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

//ʵ�ֺ��������ֱ��
void test04()
{
	initgraph(640, 200);
	for (int y = 0; y <= 200; y = y + 5)
	{
		if (y / 5 % 2 == 0)		//�ж���ż��
			setcolor(RGB(255, 0, 0));
		else
			setcolor(RGB(0, 0, 255));
		line(0, y, 640, y);
	}
	_getch();
	closegraph();
}

//����Χ������
void test05()
{
	int step = 30;
	//��ʼ�滭����
	initgraph(600, 600);
	//���ñ�����ɫΪ��ɫ
	setbkcolor(YELLOW);
	//�ñ���ɫ�����Ļ
	cleardevice();

	setlinestyle(PS_SOLID, 2);			//��ʵ��  ���Ϊ��������
	setcolor(RGB(0, 0, 0));				//����Ϊ��ɫ

	int i;
	for (i = 1; i <= 19; i++)
	{
		line(i * step, 1 * step, i * step, 19 * step);//���ƺ���
		line(1 * step, i * step, 19 * step, i * step);//��������
	}
	_getch();
	closegraph();
}

//���ƹ�������
void test06()
{
	int step = 50;
	//���ƻ���
	initgraph(500, 500);
	//���ñ�����ɫΪ��ɫ
	setbkcolor(YELLOW);
	//ʹ�ñ���ɫ�����Ļ
	cleardevice();

	int i, j;
	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if ((i + j) % 2 == 1)
			{
				setfillcolor(BLACK);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);//���ƺ�ɫש��
				//solidrectangle()��˵�  �Ҷ˵�
			}
			else
			{
				setfillcolor(WHITE);
				solidrectangle(i * step, j * step, (i + 1) * step, (j + 1) * step);//���ư�ɫש��
			}
		}
	}
	_getch();
	closegraph();
}

//����ԭ��

/*������ͼ��--��ʱ--�����ͼ�� */

int main()
{
	test06();

	return 0;
}