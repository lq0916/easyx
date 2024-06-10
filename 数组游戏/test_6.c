#include"game.h"

//ȫ�ֱ���
#define High 25
#define Width 50			//��Ϸ����ߴ�
#define EnemyNum 5			//�л�����

int position_x, position_y;		//�ɻ���λ�� ����
int canvas[High][Width] = { 0 };		//��������
int enemy_x[EnemyNum], enemy_y[EnemyNum];			//�л���λ��

int score;				
int BulletWidth;			//�ӵ����
int EnemyMoveSpeed;			//�л����ƶ��ٶ�

//���ݵĳ�ʼ��
void startup()
{
	position_x = High - 1;
	position_y = Width / 2;
	canvas[position_x][position_y] = 1;
	int k;
	for (k = 0; k < EnemyNum; k++)
	{
		enemy_x[k] = rand() % 2;
		enemy_y[k] = rand() % Width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}
	score = 0;
	BulletWidth = 0;
	EnemyMoveSpeed = 20;

}

//��ʾ����
void show()
{
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (canvas[i][j] == 0)
				printf(" ");			//����ո�
			else if (canvas[i][j] == 1)
				printf("*");			//����ɻ�
			else if (canvas[i][j] == 2)
				printf("|");			//����ӵ�
			else if (canvas[i][j] == 3)
				printf("@");			//����л�
		}
		printf("\n");
	}
	printf("�÷֣�%3d\n", score);
	Sleep(20);
}

//���û�����޹صĸ���
void updateWithoutInput()
{
	int i, j, k;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (canvas[i][j] == 2)	
			{
				for (k = 0; k < EnemyNum; k++)
				{
				if (i == enemy_x[k] & j == enemy_y[k])
				{
					score++;			//�÷ּ�1
					printf("\a");
					if (score % 5 == 0 && EnemyMoveSpeed > 3)		//�ﵽһ�����ֵл��任
						EnemyMoveSpeed--;
					if (score % 5 == 0)//�ﵽһ�������ӵ��������
						BulletWidth++;
					canvas[enemy_x[k]][enemy_y[k]] == 0;
					enemy_x[k] = 0;
					enemy_y[k] = rand() % Width;		//�����µķɻ�
					canvas[enemy_x[k]][enemy_y[k]] = 3;
					canvas[i][j] = 0;		//�ӵ���ʧ
				}
				}
				//�ӵ�����
				canvas[i][j] = 0;
				if (i > 0)
					canvas[i - 1][j] = 2;
			}
		}
	}
	static int speed = 0;
	if (speed <EnemyMoveSpeed)
	{
		speed++;
	}
	for (k = 0; k < EnemyNum; k++)
	{
		if (position_x == enemy_x[k] && position_y == enemy_y[k])//�л���ɻ���ײ
		{
			printf("��Ϸʧ�ܣ�\n");
			printf("\a\a\a");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		if (enemy_x[k] > High)
		{
			score--;
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = 0;
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
		}
		if (speed == EnemyMoveSpeed)
		{
			for (k = 0; k < EnemyNum; k++)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0;
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}
}

//���û�����йصĸ���
void updateWithInput()
{
	char input;
	if (_kbhit())
	{
		input = _getch();
			if (input == 'a'&& position_y>0)
			{
				canvas[position_x][position_y] = 0;
				position_y--;			//λ������
				canvas[position_x][position_y] = 1;
			}
			else if (input == 'd'&& position_y<Width)
			{
				canvas[position_x][position_y] = 0;
				position_y++;			//λ������
				canvas[position_x][position_y] = 1;
			}
			else if (input == 'w'&& position_x>1)
			{
				canvas[position_x][position_y] = 0;
				position_x--;			//λ������
				canvas[position_x][position_y] = 1;
			}
			else if (input == 's'&& position_x<High-1)
			{
				canvas[position_x][position_y] = 0;
				position_x++;			//λ������
				canvas[position_x][position_y] = 1;
			}
			else if (input = ' ')
			{
				int left = position_y - BulletWidth;
				int right = position_y + BulletWidth;
				if (left < 0)
					left = 0;
				if (right > Width - 1)
					right = Width - 1;
				int k;
				for(k=left;k<=right;k++)
				canvas[position_x-1][k] = 2;
			}
	}
}

int main()
{
	HideCursor();
	startup();
	while (1)
	{
		show();
		updateWithoutInput();
		updateWithInput();
	}
	return 0;
}