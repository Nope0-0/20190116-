#include "BlastFoePlaneBox.h"


CBlastFoePlaneBox::CBlastFoePlaneBox(void)
{
}


CBlastFoePlaneBox::~CBlastFoePlaneBox(void)
{
	// ���� ���վۺ϶���
	auto it = m_lstBlastPlane.begin();
	while(it != m_lstBlastPlane.end())
	{
		delete (*it);
		*it = 0 ;
		it = m_lstBlastPlane.erase(it);
		//++it;
	}
}


void CBlastFoePlaneBox::AllBlastPlaneShow(HDC hMenDC)
{
	for(auto Val : m_lstBlastPlane )
		Val->FoePlaneShow(hMenDC);
}
//�л���ʾ : ��ʱ��ShowID-- , ShowID= 0 ; ����
void CBlastFoePlaneBox::ChangeShowID()
{
	auto it = m_lstBlastPlane.begin();
	while(it != m_lstBlastPlane.end())
	{
		//ÿ�β���һ���ڵ�
		if(  (*it)->m_nShowID == 0 )
		{
			delete (*it);
			*it = 0 ;
			it = m_lstBlastPlane.erase(it);
		}
		else
		{
			(*it)->m_nShowID -- ;
			++it;
		}
	}
}

