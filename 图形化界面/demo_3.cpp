#include<graphics.h>
#include<conio.h>

int main()
{
	initgraph(640, 480);
	HWND h = GetHWnd();
		SetWindowText(h, _T("��꽻��"));
	MOUSEMSG m;					//���������Ϣ
	while (1)
	{
		m = GetMouseMsg();		//��ȡһ�����xiaoxi
		if (m.uMsg == WM_MOUSEMOVE)
		{
			//����ƶ���ʱ��С��
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

