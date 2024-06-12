#include<graphics.h>
#include<conio.h>

int main()
{
	initgraph(640, 480);
	HWND h = GetHWnd();
		SetWindowText(h, _T("鼠标交互"));
	MOUSEMSG m;					//定义鼠标消息
	while (1)
	{
		m = GetMouseMsg();		//获取一条鼠标xiaoxi
		if (m.uMsg == WM_MOUSEMOVE)
		{
			//鼠标移动的时候画小点
			putpixel(m.x, m.y, WHITE);
		}
		else if (m.uMsg == WM_LBUTTONDOWN)
		{
			rectangle(m.x - 5, m.y - 5, m.x + 5, m.y + 5);
		}
		else if (m.uMsg == WM_RBUTTONUP)
		{
			circle(m.x, m.y, 10);
		}

	}
	return 0;
}

