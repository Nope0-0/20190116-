#include "FoePlaneBig.h"

//��ɻ��ĳߴ� : 108 * 128
CFoePlaneBig::CFoePlaneBig(void)
{
	m_hBmpFoePlane	= 0 ;
	m_nBlood			= 5 ;
	m_nShowID		= 3 ;
	m_nX				= rand()%( 380 - 108 ) ;
	m_nY				= -128 ;
}


CFoePlaneBig::~CFoePlaneBig(void)
{
	::DeleteObject(m_hBmpFoePlane);
}

//�ж��ӵ��Ƿ�ײ������
bool CFoePlaneBig::IsHitByGunner(CGunner *pGunner)
{
	if( pGunner->m_nX >= m_nX && pGunner->m_nX +6 <= m_nX + 108 
		&& pGunner->m_nY >= m_nY && pGunner->m_nY + 9 <= m_nY + 128 )
		return true; 
	return false;
}
bool CFoePlaneBig::IsHitPlayer(CPlayer & Player)	
{
	//( x + 30 , y +30 ) (x+30 , y) ( x, Y+50) (x+60, y+50)
	int x = 0, y = 0 ;
	x= Player.m_nX + 30 ; y = Player.m_nY + 30;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX + 30 ; y = Player.m_nY ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX +60 ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	return false;
}
void CFoePlaneBig::FoePlaneInit(HINSTANCE hIns)	
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BIG));
}
void CFoePlaneBig::FoePlaneMove()				
{
	//��һְ�� ֻ�����ƶ� ������ �������� , ����������λ��Box����
	m_nY += 1;
}
void CFoePlaneBig::FoePlaneShow(HDC hMenDC)		
{
	//1. ����Ŀ��DC�ļ���DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpFoePlane);
	//3. ������DC�����λͼ����Ŀ��DC  ȥ��ͼƬ������ɫ  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY,108, 128,hdc,0, (3 - m_nShowID)*128,/*SRCCOPY*/ SRCAND );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��
	// ������Դ
	::DeleteDC(hdc);
}