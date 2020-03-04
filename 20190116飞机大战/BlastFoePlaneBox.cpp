#include "BlastFoePlaneBox.h"


CBlastFoePlaneBox::CBlastFoePlaneBox(void)
{
}


CBlastFoePlaneBox::~CBlastFoePlaneBox(void)
{
	// 析构 回收聚合对象
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
//切换显示 : 定时将ShowID-- , ShowID= 0 ; 回收
void CBlastFoePlaneBox::ChangeShowID()
{
	auto it = m_lstBlastPlane.begin();
	while(it != m_lstBlastPlane.end())
	{
		//每次操作一个节点
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

