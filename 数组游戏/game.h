#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

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
