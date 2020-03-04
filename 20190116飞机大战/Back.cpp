#include "Back.h"


CBack::CBack(void)
{
	m_hBmpBackDown	= 0 ;
	m_hBmpBackUp		= 0 ;
	m_nX				= 0 ;
	m_nY				= 0 ;
}


CBack::~CBack(void)
{
	::DeleteObject(m_hBmpBackDown);
	::DeleteObject(m_hBmpBackUp);
}

void CBack::BackInit(HINSTANCE hIns)
{
	m_hBmpBackDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BACK));
	m_hBmpBackUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BACK));
}
void CBack::BackMove()
{
	if( m_nY >= 550 )
	{
		m_nY = 0 ;
	}
	else
	{
		m_nY++;
	}
}
void CBack::BackShow(HDC hMenDC) // hMenDC 目标DC
{
	//1. 创建目标DC的兼容DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. 将位图传到兼容DC
	::SelectObject(hdc,m_hBmpBackDown);
	//3. 将兼容DC里面的位图传到目标DC
	::BitBlt(hMenDC,m_nX,m_nY,380, 550,hdc,0,0,SRCCOPY );//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴

	//2. 将位图传到兼容DC
	::SelectObject(hdc,m_hBmpBackUp);
	//3. 将兼容DC里面的位图传到目标DC
	::BitBlt(hMenDC,m_nX, m_nY - 550 ,380, 550,hdc,0,0,SRCCOPY );//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴

	// 回收资源
	::DeleteDC(hdc);
}
