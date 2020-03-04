#include "ToolBoom.h"


CToolBoom::CToolBoom(void)
{
	m_nStyle = 1;
}


CToolBoom::~CToolBoom(void)
{
	::DeleteObject(m_hBmpTool);
}

void CToolBoom::ToolShow(HDC hMenDC)
{
		//创建兼容DC
	HDC hdc = ::CreateCompatibleDC(hMenDC);
	//将位图传到兼容dc
	::SelectObject(hdc,m_hBmpTool);
	//将DC里面的位图传给目标DC   //解决问题: 飞机背景白色 使用 SRCAND 透明显示背景
	::BitBlt(hMenDC,m_nX,m_nY,/*48*/32,/*48*/32,hdc,/*0*/1,0,/*SRCCOPY*/SRCAND); // 目标DC , 在界面那个位置画, 贴多大,来自哪个DC , 从图片的哪个位置开始, 怎么贴
	//回收兼容DC
	::DeleteDC(hdc);
}
void CToolBoom::ToolInit(HINSTANCE hIns , int x, int y)
{
	m_hBmpTool = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_TOOL));
	m_nX = x; 
	m_nY = y;
}
