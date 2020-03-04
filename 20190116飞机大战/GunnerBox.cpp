#include "GunnerBox.h"


CGunnerBox::CGunnerBox(void)
{
}


CGunnerBox::~CGunnerBox(void)
{
	// ���� ���վۺ϶���
	list<CGunner*> :: iterator /*auto*/ it = m_lstGunner.begin();
	while(it != m_lstGunner.end())
	{
		delete (*it);
		*it = 0 ;
		it = m_lstGunner.erase(it);
		//++it;
	}
}

//3.4 �ӵ��ƶ��ᳬ����ʾ��Χ, ɾ������
void CGunnerBox::AllGunnerMove()
{
	auto it = m_lstGunner.begin();
	while(it != m_lstGunner.end())
	{
		//ÿ�β���һ���ڵ�
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
	//��������.,������ʾ  ʹ�÷�Χfor
	for( CGunner* pGunner :  m_lstGunner )
	{
		pGunner->GunnerShow(hMenDC);
	}
}

