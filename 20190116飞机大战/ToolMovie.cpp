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
	//��������DC
	HDC hdc = ::CreateCompatibleDC(hMenDC);
	//��λͼ��������dc
	::SelectObject(hdc,m_hBmpMovie[m_nIndex++]);
	//��DC�����λͼ����Ŀ��DC   //�������: �ɻ�������ɫ ʹ�� SRCAND ͸����ʾ����
	::BitBlt(hMenDC,m_nX,m_nY,380,550,hdc,0,0,/*SRCCOPY*/SRCAND); // Ŀ��DC , �ڽ����Ǹ�λ�û�, �����,�����ĸ�DC , ��ͼƬ���ĸ�λ�ÿ�ʼ, ��ô��
	//���ռ���DC
	::DeleteDC(hdc);
}
