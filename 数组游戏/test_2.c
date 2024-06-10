#include<Stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

//ȫ�ֱ���
int position_x, position_y;			//�ɻ�λ��
int bullet_x, bullet_y;			   //�ӵ�λ��
int enemy_x, enemy_y;				//�л�λ��
int high, width;					//��Ϸ����ߴ�
int score;


//���ݳ�ʼ��
void startup()
{
	high = 20;
	width = 30;
	position_x = high / 2;
	position_y = width / 2;
	bullet_x = 0;
	bullet_y = position_x;
	enemy_x = 0;
	enemy_y = position_y;
	score = 0;
}

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //�ڶ���ֵΪ0����ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//����Ƶ�(X,Y)λ��
void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}


//��ʾ����
void show()
{
	gotoxy(0, 0);//����ȡ��system("cls");  //���Ǵ����ӳ�
	//system("cls");
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i == position_x && j == position_y)
				printf("*");	//����ɻ�*	
			else if (i == enemy_x && j == enemy_y)
				printf("@");	//����л�@
			else if (i == bullet_x && j == bullet_y)
				printf("|");	//����ӵ�|
			else
				printf(" ");	//����ո�
		}
		printf("\n");
	}
	printf("�÷�: %d\n", score);
}

//���û������޹صĸ���
void updatewithoutInput()
{
	if (bullet_x > -1)
		bullet_x--;
	if (bullet_x == enemy_x && bullet_y == enemy_y)
	{
		score++;
		enemy_x = -1;;			//�����µĵл�
		enemy_y = rand() % width;
		bullet_x = -2;
	}
	if (enemy_x > high)//�л��ܳ���Ļ��
	{
		enemy_x = -1;
		enemy_y = rand() % width;
		score -= 2;
	}
	//�������Ƶл��½����ٶȣ�ÿ������ѭ�����ƶ�һ�εл�
	//�����л����ٶȵ��ƶ���ʾ���Խ���
	static int speed = 0;
	int num;
	num = 10;
	if (speed < num)
		speed++;
	//if (score % 3 == 1) num--;  //���������ٶȼӿ�
	if (speed==num)
	{
		enemy_x++;
		speed = 0;
	}
	
}

//���û������йصĸ���
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();

		if (input == 'a')
			if(position_y>1) position_y--;
		if (input == 'd')
			if(position_y<width-1) position_y++;
		if (input == 'w')
			if(position_x>1)	position_x--;
		if (input == 's')
			if(position_x<high-1)	position_x++;
		if (input == ' ')
		{
			bullet_x = position_x - 1;
			bullet_y = position_y;
		}
	
	}
}

//������
int main_22()
{
	startup();
	HideCursor();    //���ع��
	while (1)
	{
		show();
		updatewithoutInput();
		updateWithInput();
		Sleep(50);
	}
	return 0;
}
