#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#define High 50
#define Width 50		//游戏画面尺寸

//全局变量
int cells[High][Width];

// 光标移到(X, Y)位置
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //第二个值为0，表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//数据初始化
void startup()
{
	int i, j;
	for(i=0;i<High;i++)
		for (j = 0; j < Width; j++)
		{
			cells[i][j] = 1;//rand() % 2;
		}
}

//显示画面
void show()
{
	gotoxy(0,0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (cells[i][j] == 1)
				printf("*");		//输出活得细胞
			else
				printf(" ");		//输出空格
		}
		printf("\n");
	}
	Sleep(50);
}

//与用户无关的更新
void updateWithoutInput()
{
	int NewCells[High][Width];	//下一帧的细胞情况
	int NeibourNumber;			//统计邻居的个数
	int i, j;
	for (i = 1; i < High; i++)
	{
		for (j = 1; j < Width; j++)
		{
			NeibourNumber=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+
				cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
			if (NeibourNumber == 3)
				NewCells[i][j] = 1;
			else if (NeibourNumber == 2)
				NewCells[i][j] = cells[i][j];
			else
				NewCells[i][j] = 0;
		}
	}
	for (i = 1; i < High; i++)
		for (j = 1; j < Width; j++)
			cells[i][j] = NewCells[i][j];;		
}

//与用户有关输出得更新
void updateWithInput()
{

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
}