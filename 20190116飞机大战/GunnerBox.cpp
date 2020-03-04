#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	// 析构 回收聚合对象
	list<CGunner*> :: iterator /*auto*/ it = m_lstGunner.begin();
	while(it != m_lstGunner.end())
	{
		delete (*it);
		*it = 0 ;
		it = m_lstGunner.erase(it);
		//++it;
	}
}

//3.4 子弹移动会超出显示范围, 删除对象
void CGunnerBox::AllGunnerMove()
{
	auto it = m_lstGunner.begin();
	while(it != m_lstGunner.end())
	{
		//每次操作一个节点
		if( (*it)->m_nY < 0  )
		{
			delete (*it);
			*it = 0 ;
			it = m_lstGunner.erase(it);
		}
		else
		{
			(*it)->GunnerMove();
			++it;
		}
	}
}
void CGunnerBox::AllGunnerShow(HDC hMenDC)
{
	//遍历链表.,调用显示  使用范围for
	for( CGunner* pGunner :  m_lstGunner )
	{
		pGunner->GunnerShow(hMenDC);
	}
}

