#include<Stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

//全局变量
int position_x, position_y;			//飞机位置
int bullet_x, bullet_y;			   //子弹位置
int enemy_x, enemy_y;				//敌机位置
int high, width;					//游戏画面尺寸
int score;


//数据初始化
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

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //第二个值为0，表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//光标移到(X,Y)位置
void gotoxy(int x,int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}


//显示画面
void show()
{
	gotoxy(0, 0);//可以取代system("cls");  //但是存在延迟
	//system("cls");
	int i, j;
	for (i = 0; i < high; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i == position_x && j == position_y)
				printf("*");	//输出飞机*	
			else if (i == enemy_x && j == enemy_y)
				printf("@");	//输出敌机@
			else if (i == bullet_x && j == bullet_y)
				printf("|");	//输出子弹|
			else
				printf(" ");	//输出空格
		}
		printf("\n");
	}
	printf("得分: %d\n", score);
}

//与用户输入无关的更新
void updatewithoutInput()
{
	if (bullet_x > -1)
		bullet_x--;
	if (bullet_x == enemy_x && bullet_y == enemy_y)
	{
		score++;
		enemy_x = -1;;			//产生新的敌机
		enemy_y = rand() % width;
		bullet_x = -2;
	}
	if (enemy_x > high)//敌机跑出屏幕外
	{
		enemy_x = -1;
		enemy_y = rand() % width;
		score -= 2;
	}
	//用来控制敌机下降的速度，每隔几次循环才移动一次敌机
	//这样敌机的速度的移动显示可以降速
	static int speed = 0;
	int num;
	num = 10;
	if (speed < num)
		speed++;
	//if (score % 3 == 1) num--;  //分数增加速度加快
	if (speed==num)
	{
		enemy_x++;
		speed = 0;
	}
	
}

//与用户输入有关的更新
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

//主函数
int main_22()
{
	startup();
	HideCursor();    //隐藏光标
	while (1)
	{
		show();
		updatewithoutInput();
		updateWithInput();
		Sleep(50);
	}
	return 0;
}
