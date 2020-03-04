#include "FoePlaneBox.h"
#include "FoePlaneBig.h"
#include "FoePlaneMid.h"
#include "FoePlaneSmall.h"

CFoePlaneBox::CFoePlaneBox(void)
{
}


CFoePlaneBox::~CFoePlaneBox(void)
{
	// 析构 回收聚合对象
	auto it = m_lstFoePlane.begin();
	while(it != m_lstFoePlane.end())
	{
		delete (*it);
		*it = 0 ;
		it = m_lstFoePlane.erase(it);
		//++it;
	}
}

//移动会超出显示范围, 删除对象
void CFoePlaneBox::AllFoePlaneMove()
{
	auto it = m_lstFoePlane.begin();
	while(it != m_lstFoePlane.end())
	{
		//每次操作一个节点
		if( (*it)->m_nY > 550  )
		{
			delete (*it);
			*it = 0 ;
			it = m_lstFoePlane.erase(it);
		}
		else
		{
			(*it)->FoePlaneMove();
			++it;
		}
	}
}
void CFoePlaneBox::AllFoePlaneShow(HDC hMenDC)
{
	//遍历链表.,调用显示  使用范围for
	for( auto Val :  m_lstFoePlane )
	{
		Val->FoePlaneShow(hMenDC);
	}
}
void CFoePlaneBox::FoePlaneCreate(HINSTANCE hIns)
{
	int nRand = rand()%10;  // 0-9
	//new ?  三种子飞机
	CFoePlane * pFoePlane = 0 ;
	switch( nRand )
	{
	case 0: case 1: case 2 : case 3:
		pFoePlane = new CFoePlaneSmall;
		break;
	case 4: case 5: case 6 : 
		pFoePlane = new CFoePlaneMid;
		break;
	case 7: case 8:
		pFoePlane = new CFoePlaneBig;
		break;
	default: break;
	}
	if( pFoePlane )
	{
		pFoePlane->FoePlaneInit(hIns);
		m_lstFoePlane.push_back(pFoePlane);
	}
}

 
 
