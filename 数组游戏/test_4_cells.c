#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#define High 50
#define Width 50		//��Ϸ����ߴ�

//ȫ�ֱ���
int cells[High][Width];

// ����Ƶ�(X, Y)λ��
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };  //�ڶ���ֵΪ0����ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//���ݳ�ʼ��
void startup()
{
	int i, j;
	for(i=0;i<High;i++)
		for (j = 0; j < Width; j++)
		{
			cells[i][j] = 1;//rand() % 2;
		}
}

//��ʾ����
void show()
{
	gotoxy(0,0);
	int i, j;
	for (i = 0; i < High; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (cells[i][j] == 1)
				printf("*");		//������ϸ��
			else
				printf(" ");		//����ո�
		}
		printf("\n");
	}
	Sleep(50);
}

//���û��޹صĸ���
void updateWithoutInput()
{
	int NewCells[High][Width];	//��һ֡��ϸ�����
	int NeibourNumber;			//ͳ���ھӵĸ���
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

//���û��й�����ø���
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