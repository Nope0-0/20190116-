#include "Gunner.h"

//�ӵ��ĳߴ� 6 * 9 
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
	//��һְ�� , ֻ���ƶ��������� , Խ�紦������
	m_nY -= 10;
}
void CGunner::GunnerShow(HDC hMenDC)
{
	//1. ����Ŀ��DC�ļ���DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpGunner);
	//3. ������DC�����λͼ����Ŀ��DC  ȥ��ͼƬ������ɫ  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY, 6 , 9,hdc,0,0,/*SRCCOPY*/ SRCAND );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��
	// ������Դ
	::DeleteDC(hdc);
}