#include "ToolMovie.h"


CToolMovie::CToolMovie(void)
{
	m_bFlag = false;
	for(auto it :m_hBmpMovie)
	it = 0 ;
	m_nX = 0 ;
	m_nY = 0 ;
	m_nIndex = 0;
}


CToolMovie::~CToolMovie(void)
{
	for(auto it :m_hBmpMovie)
	::DeleteObject(it);
}

void CToolMovie::ToolMovieInit(HINSTANCE hIns)
{
	 m_hBmpMovie[0] = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BOOM1));
	 m_hBmpMovie[1] = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BOOM2));
	 m_hBmpMovie[2] = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BOOM3));
	 m_hBmpMovie[3] = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BOOM4));
	 m_hBmpMovie[4] = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BOOM4));
}
void CToolMovie::ToolMovieShow(HDC hMenDC )
{
	//创建兼容DC
	HDC hdc = ::CreateCompatibleDC(hMenDC);
	//将位图传到兼容dc
	::SelectObject(hdc,m_hBmpMovie[m_nIndex++]);
	//将DC里面的位图传给目标DC   //解决问题: 飞机背景白色 使用 SRCAND 透明显示背景
	::BitBlt(hMenDC,m_nX,m_nY,380,550,hdc,0,0,/*SRCCOPY*/SRCAND); // 目标DC , 在界面那个位置画, 贴多大,来自哪个DC , 从图片的哪个位置开始, 怎么贴
	//回收兼容DC
	::DeleteDC(hdc);
}
