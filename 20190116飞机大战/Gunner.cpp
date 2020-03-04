#include "Gunner.h"

//子弹的尺寸 6 * 9 
CGunner::CGunner(void)
{
	m_hBmpGunner	= 0 ;
	m_nX			= 0 ;
	m_nY			= 0 ;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hBmpGunner);
}


void CGunner::GunnerInit(HINSTANCE hIns, int x, int y)
	
{
	m_hBmpGunner = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_GUNNER));
	m_nX	 = x;
	m_nY	 = y;
}
void CGunner::GunnerMove()
{
	//单一职责 , 只管移动不管销毁 , 越界处理不在这
	m_nY -= 10;
}
void CGunner::GunnerShow(HDC hMenDC)
{
	//1. 创建目标DC的兼容DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. 将位图传到兼容DC
	::SelectObject(hdc,m_hBmpGunner);
	//3. 将兼容DC里面的位图传到目标DC  去除图片背景颜色  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY, 6 , 9,hdc,0,0,/*SRCCOPY*/ SRCAND );//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴
	// 回收资源
	::DeleteDC(hdc);
}