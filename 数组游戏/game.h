#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

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
