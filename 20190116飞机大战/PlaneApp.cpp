#include "PlaneApp.h"

CREATE(CPlaneApp)

WINDOW_HEIGHT(550)
WINDOW_WIDTH(380)

CPlaneApp::CPlaneApp(void)
{
	//DC ��ֵ
	hdc = 0;
	//����DC ��ֵ
	hMenDC = 0;
	//����λͼ��ֵ
	hMenBmp = 0;
	
	m_pTool = 0;
}


CPlaneApp::~CPlaneApp(void)
{
	//�ͷŻ�����Դ
	::DeleteDC(hMenDC);
	::DeleteObject(hMenBmp);
	::ReleaseDC(this->m_hMainWnd,hdc);
}

void CPlaneApp::onGameCreate() //��Ϸ����,������ʼ��,����λͼ :ʵ����� HINSTANCE
{
	//================ ��ͼ��Դ�ĳ�ʼ��=========================
	//��ô��ڶ�Ӧ��DC
	hdc = ::GetDC(this->m_hMainWnd);
	//��������DC 
	hMenDC = ::CreateCompatibleDC(hdc);
	//��������λͼ
	hMenBmp = ::CreateCompatibleBitmap(hdc,380,550);
	//����λͼ�ŵ�����DC����
	::SelectObject(hMenDC,hMenBmp);
	//================ ��ͼ��Դ�ĳ�ʼ��=========================
	//1. ������ʼ��
	m_Back.BackInit( this->m_hIns);
	//2. ��ҷɻ���ʼ��
	m_Player.PlayerInit(this->m_hIns);

	m_ToolMovie.ToolMovieInit(m_hIns);
	//3. �������ж�ʱ��
	SetAllTimer();
}
void CPlaneApp::onGameDraw() //��ͼHDC GetDC() ���봰�ھ��: ���ھ��
{
	//----------------˫������ʾ--------------------------------
	//��ͼ
	//1.������ʾ
	m_Back.BackShow(hMenDC);
	//2.��ҷɻ���ʾ
	m_Player.PlayerShow(hMenDC);
	//3.�ڵ���ʾ
	m_GunnerBox.AllGunnerShow(hMenDC);
	//4.���˷ɻ���ʾ
	m_FoePlaneBox.AllFoePlaneShow(hMenDC);
	//5.��ը���˷ɻ���ʾ
	m_BlastFoePlaneBox.AllBlastPlaneShow(hMenDC);

	if( m_pTool )
		m_pTool->ToolShow(hMenDC);

	if( m_ToolMovie .m_bFlag )
	{
		if( m_ToolMovie.m_nIndex >= 5)
		{
			ClearAllFoePlane();
			m_ToolMovie.m_nIndex = 0;
			m_ToolMovie .m_bFlag = false;
			KillTimer(m_hMainWnd , TOOL_MOVIE_TIMER_ID);
			SetAllTimer();
		}
		else	
		m_ToolMovie.ToolMovieShow(hMenDC);	
	}	
	//������DC���滭��ͼ, ����Ŀ��DC��
	::BitBlt(hdc,0,0,380,550,hMenDC,0,0,SRCCOPY);//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��
	//----------------˫������ʾ--------------------------------
	
}
void CPlaneApp::onGameRun( WPARAM nTimerID) //��ʱ��, �ĸ���ʱ��
{
	//��Ҽ�ⰴ����ʱ�� 
	if( PLAYER_MOVE_TIMER_ID == nTimerID	)
	{
		//�����Ұ���
		if( ::GetAsyncKeyState(VK_LEFT))
			m_Player.PlayerMove(VK_LEFT);
		if( ::GetAsyncKeyState(VK_RIGHT))
			m_Player.PlayerMove(VK_RIGHT);
		if( ::GetAsyncKeyState(VK_UP))
			m_Player.PlayerMove(VK_UP);
		if( ::GetAsyncKeyState(VK_DOWN))
			m_Player.PlayerMove(VK_DOWN);
	}
	//�����ƶ��Ķ�ʱ��
	if( BACK_MOVE_TIMER_ID == nTimerID	)
	{
		m_Back.BackMove();
	}
	//��ҷɻ������ڵ���ʱ��,
	if( PLAYER_SEND_GUNNER_TIMER_ID == nTimerID	)
	{
		m_Player.PlayerSendGunner(this->m_hIns,m_GunnerBox);
	}
	//�ڵ��ƶ���ʱ��
	if( GUNNER_MOVE_TIMER_ID == nTimerID	)
	{
		m_GunnerBox.AllGunnerMove();
		GunnersHitFoePlanes();
	}
	//���˷ɻ�������ʱ��,
	if( FOEPLANE_CREATE_TIMER_ID == nTimerID	)
	{
		m_FoePlaneBox.FoePlaneCreate(this->m_hIns);
	}
	//���˷ɻ��ƶ���ʱ��
	if( FOEPLANE_MOVE_TIMER_ID == nTimerID	)
	{
		m_FoePlaneBox.AllFoePlaneMove();
		//�����ƶ����ж��Ƿ���Ϸ����
		if( this->IsGameOver())
		{
			//�Ȼ�һ��ͼ
			this->onGameDraw();
			//�ر����ж�ʱ��
			KillAllTimer();
			//������ʾ, �˳�
			if( ::MessageBox(this->m_hMainWnd , "��Ϸ����","��ʾ" , MB_OK) )
			{
				::PostQuitMessage(0);//WM_CLOSE
			}
		}
	}
	//��ը���˷ɻ��л���ʾ��ʱ��
	if( BLAST_FOEPLANE_SHOW_TIMER_ID == nTimerID	)
	{
		m_BlastFoePlaneBox.ChangeShowID();
	}
	if( TOOL_MOVE_TIMER_ID == nTimerID )
	{
		if( m_pTool )
		{
			if( m_Player.IsPlayerEatTool( m_pTool ) )
			{
				if( m_pTool->m_nStyle == 0 )
				{
					m_Player.ChangeGunnerStyle();	
				}		
				if( m_pTool->m_nStyle == 1 )
				{
					KillAllTimer();
					SetTimer( m_hMainWnd , TOOL_MOVIE_TIMER_ID,500,0 );
					m_ToolMovie .m_bFlag = true;
				}
				delete m_pTool;
					m_pTool = 0;
			}
		}	
		if(m_pTool)
		{
			m_pTool->ToolMove();
		}
	}
	//�ػ�
	this->onGameDraw();
}
void CPlaneApp::onKeyDown(WPARAM nKey) //���°���, ���ĸ���
{
	////����ƶ�
	//if( nKey == VK_LEFT || nKey == VK_RIGHT||nKey == VK_UP||nKey == VK_DOWN)
	//{
	//	//����ƶ�
	//	m_Player.PlayerMove(nKey);
	//}
	////�ػ�
	//this->onGameDraw();
}

//ײ������ ����Ҫ��Ѫ,�ӵ�Ҫɾ���ж��Ƿ�ը��ը�Ļ�, �ӵ���Box�����Ƴ�, Ȼ���ƶ�����ըBox
void CPlaneApp::GunnersHitFoePlanes()//�ӵ�ײ������
{
	bool bFlag = false;
	//���������ӵ� ,�õ�һ���ӵ�
	auto itGunner = m_GunnerBox.m_lstGunner.begin();
	while(itGunner != m_GunnerBox.m_lstGunner.end())
	{
		//�������˷ɻ�, �õ�һ������
		auto itFoePlane = m_FoePlaneBox.m_lstFoePlane.begin();
		while( itFoePlane != m_FoePlaneBox.m_lstFoePlane.end())
		{
			// �ж�һ���ӵ���һ�������Ƿ�ײ��һ��
			if( ( *itFoePlane)->IsHitByGunner(*itGunner ) )
			{
				bFlag = true;
				//ײ������ ����Ҫ��Ѫ,�ӵ�Ҫɾ��
				delete (*itGunner );
				(*itGunner ) = 0;
				itGunner = m_GunnerBox.m_lstGunner.erase(itGunner);

				( *itFoePlane)->BloodDown();
				//�ж��Ƿ�ը
				if( ( *itFoePlane)->IsBoom() )
				{//��ը�Ļ�, �ӵ���Box�����Ƴ�, Ȼ���ƶ�����ըBox
					if( !m_pTool)
					m_pTool = (* itFoePlane)->ToolCreate(this->m_hIns);
					// TODO: �ƶ�����ըBox
					m_BlastFoePlaneBox.m_lstBlastPlane.push_back( *itFoePlane );
					itFoePlane = m_FoePlaneBox.m_lstFoePlane.erase(itFoePlane);
				}
				break;//�ӵ������, ���ü�������������
			}
			++itFoePlane;
		}
		if( !bFlag )
			++itGunner;
		else 
			bFlag = false;
	}
}

bool CPlaneApp::IsGameOver()
{
	//�������е���, Ȼ��ȥ�ж�ÿ�������Ƿ�ײ�������
	auto it = m_FoePlaneBox.m_lstFoePlane.begin();
	while(it != m_FoePlaneBox.m_lstFoePlane.end())
	{
		if( (*it)->IsHitPlayer( m_Player))
		{
			return true;
		}
		++it;
	}
	return false;
}

void CPlaneApp::SetAllTimer()
{
	//3.1�����ƶ��Ķ�ʱ��,BACK_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,BACK_MOVE_TIMER_ID,50,0);
	//3.2��ҷɻ������ڵ���ʱ��,PLAYER_SEND_GUNNER_TIMER_ID
	::SetTimer(this->m_hMainWnd,PLAYER_SEND_GUNNER_TIMER_ID,350,0);
	//3.3�ڵ��ƶ���ʱ��GUNNER_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);
	//3.4���˷ɻ�������ʱ��,FOEPLANE_CREATE_TIMER_ID
	::SetTimer(this->m_hMainWnd,FOEPLANE_CREATE_TIMER_ID,1000,0);
	//3.5���˷ɻ��ƶ���ʱ��,FOEPLANE_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,10,0);
	//3.6��ը���˷ɻ��л���ʾ��ʱ��,BLAST_FOEPLANE_SHOW_TIMER_ID
	::SetTimer(this->m_hMainWnd,BLAST_FOEPLANE_SHOW_TIMER_ID,150,0);
	//3.7��Ҽ�ⰴ����ʱ�� PLAYER_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);
	//3.8�����ƶ� TOOL_MOVE_TIMER_ID
	::SetTimer(m_hMainWnd , TOOL_MOVE_TIMER_ID,10,0);
}
//�ر����ж�ʱ
void CPlaneApp::KillAllTimer()
{
	//3.1�����ƶ��Ķ�ʱ��,BACK_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,BACK_MOVE_TIMER_ID);
	//3.2��ҷɻ������ڵ���ʱ��,PLAYER_SEND_GUNNER_TIMER_ID
	::KillTimer(this->m_hMainWnd,PLAYER_SEND_GUNNER_TIMER_ID);
	//3.3�ڵ��ƶ���ʱ��GUNNER_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,GUNNER_MOVE_TIMER_ID);
	//3.4���˷ɻ�������ʱ��,FOEPLANE_CREATE_TIMER_ID
	::KillTimer(this->m_hMainWnd,FOEPLANE_CREATE_TIMER_ID);
	//3.5���˷ɻ��ƶ���ʱ��,FOEPLANE_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);
	//3.6��ը���˷ɻ��л���ʾ��ʱ��,BLAST_FOEPLANE_SHOW_TIMER_ID
	::KillTimer(this->m_hMainWnd,BLAST_FOEPLANE_SHOW_TIMER_ID);
	//3.7��Ҽ�ⰴ����ʱ�� PLAYER_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,PLAYER_MOVE_TIMER_ID);
	//3.8�����ƶ� TOOL_MOVE_TIMER_ID
	::KillTimer(m_hMainWnd , TOOL_MOVE_TIMER_ID);
}

void CPlaneApp::ClearAllFoePlane()
{
	//�������е���, �õ�һ������
	auto itFoePlane = m_FoePlaneBox.m_lstFoePlane.begin();
	while( itFoePlane != m_FoePlaneBox.m_lstFoePlane.end())
	{
		if(!m_pTool)
		m_pTool = (* itFoePlane)->ToolCreate(this->m_hIns);
		//��ը���ڵ��ƶ�����ը����, ���ӵ���box�Ƴ�
		//todo: ���ڵ��ƶ�����ը����
		m_BlastFoePlaneBox.m_lstBlastPlane.push_back( (* itFoePlane) );
		itFoePlane = m_FoePlaneBox.m_lstFoePlane.erase(itFoePlane);
	}
}