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
void CBack::BackShow(HDC hMenDC) // hMenDC Ŀ��DC
{
	//1. ����Ŀ��DC�ļ���DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpBackDown);
	//3. ������DC�����λͼ����Ŀ��DC
	::BitBlt(hMenDC,m_nX,m_nY,380, 550,hdc,0,0,SRCCOPY );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��

	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpBackUp);
	//3. ������DC�����λͼ����Ŀ��DC
	::BitBlt(hMenDC,m_nX, m_nY - 550 ,380, 550,hdc,0,0,SRCCOPY );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��

	// ������Դ
	::DeleteDC(hdc);
}
