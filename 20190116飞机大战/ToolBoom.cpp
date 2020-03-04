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
		//��������DC
	HDC hdc = ::CreateCompatibleDC(hMenDC);
	//��λͼ��������dc
	::SelectObject(hdc,m_hBmpTool);
	//��DC�����λͼ����Ŀ��DC   //�������: �ɻ�������ɫ ʹ�� SRCAND ͸����ʾ����
	::BitBlt(hMenDC,m_nX,m_nY,/*48*/32,/*48*/32,hdc,/*0*/1,0,/*SRCCOPY*/SRCAND); // Ŀ��DC , �ڽ����Ǹ�λ�û�, �����,�����ĸ�DC , ��ͼƬ���ĸ�λ�ÿ�ʼ, ��ô��
	//���ռ���DC
	::DeleteDC(hdc);
}
void CToolBoom::ToolInit(HINSTANCE hIns , int x, int y)
{
	m_hBmpTool = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_TOOL));
	m_nX = x; 
	m_nY = y;
}
