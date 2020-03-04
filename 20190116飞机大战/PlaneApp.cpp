#include "PlaneApp.h"

CREATE(CPlaneApp)

WINDOW_HEIGHT(550)
WINDOW_WIDTH(380)

CPlaneApp::CPlaneApp(void)
{
	//DC 初值
	hdc = 0;
	//兼容DC 初值
	hMenDC = 0;
	//兼容位图初值
	hMenBmp = 0;
	
	m_pTool = 0;
}


CPlaneApp::~CPlaneApp(void)
{
	//释放回收资源
	::DeleteDC(hMenDC);
	::DeleteObject(hMenBmp);
	::ReleaseDC(this->m_hMainWnd,hdc);
}

void CPlaneApp::onGameCreate() //游戏创建,包含初始化,加载位图 :实例句柄 HINSTANCE
{
	//================ 绘图资源的初始化=========================
	//获得窗口对应的DC
	hdc = ::GetDC(this->m_hMainWnd);
	//创建兼容DC 
	hMenDC = ::CreateCompatibleDC(hdc);
	//创建兼容位图
	hMenBmp = ::CreateCompatibleBitmap(hdc,380,550);
	//兼容位图放到兼容DC上面
	::SelectObject(hMenDC,hMenBmp);
	//================ 绘图资源的初始化=========================
	//1. 背景初始化
	m_Back.BackInit( this->m_hIns);
	//2. 玩家飞机初始化
	m_Player.PlayerInit(this->m_hIns);

	m_ToolMovie.ToolMovieInit(m_hIns);
	//3. 开启所有定时器
	SetAllTimer();
}
void CPlaneApp::onGameDraw() //绘图HDC GetDC() 传入窗口句柄: 窗口句柄
{
	//----------------双缓冲显示--------------------------------
	//绘图
	//1.背景显示
	m_Back.BackShow(hMenDC);
	//2.玩家飞机显示
	m_Player.PlayerShow(hMenDC);
	//3.炮弹显示
	m_GunnerBox.AllGunnerShow(hMenDC);
	//4.敌人飞机显示
	m_FoePlaneBox.AllFoePlaneShow(hMenDC);
	//5.爆炸敌人飞机显示
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
	//将兼容DC上面画的图, 传到目标DC里
	::BitBlt(hdc,0,0,380,550,hMenDC,0,0,SRCCOPY);//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴
	//----------------双缓冲显示--------------------------------
	
}
void CPlaneApp::onGameRun( WPARAM nTimerID) //定时器, 哪个定时器
{
	//玩家检测按键定时器 
	if( PLAYER_MOVE_TIMER_ID == nTimerID	)
	{
		//检测玩家按键
		if( ::GetAsyncKeyState(VK_LEFT))
			m_Player.PlayerMove(VK_LEFT);
		if( ::GetAsyncKeyState(VK_RIGHT))
			m_Player.PlayerMove(VK_RIGHT);
		if( ::GetAsyncKeyState(VK_UP))
			m_Player.PlayerMove(VK_UP);
		if( ::GetAsyncKeyState(VK_DOWN))
			m_Player.PlayerMove(VK_DOWN);
	}
	//背景移动的定时器
	if( BACK_MOVE_TIMER_ID == nTimerID	)
	{
		m_Back.BackMove();
	}
	//玩家飞机发射炮弹定时器,
	if( PLAYER_SEND_GUNNER_TIMER_ID == nTimerID	)
	{
		m_Player.PlayerSendGunner(this->m_hIns,m_GunnerBox);
	}
	//炮弹移动定时器
	if( GUNNER_MOVE_TIMER_ID == nTimerID	)
	{
		m_GunnerBox.AllGunnerMove();
		GunnersHitFoePlanes();
	}
	//敌人飞机创建定时器,
	if( FOEPLANE_CREATE_TIMER_ID == nTimerID	)
	{
		m_FoePlaneBox.FoePlaneCreate(this->m_hIns);
	}
	//敌人飞机移动定时器
	if( FOEPLANE_MOVE_TIMER_ID == nTimerID	)
	{
		m_FoePlaneBox.AllFoePlaneMove();
		//敌人移动就判断是否游戏结束
		if( this->IsGameOver())
		{
			//先画一次图
			this->onGameDraw();
			//关闭所有定时器
			KillAllTimer();
			//弹窗提示, 退出
			if( ::MessageBox(this->m_hMainWnd , "游戏结束","提示" , MB_OK) )
			{
				::PostQuitMessage(0);//WM_CLOSE
			}
		}
	}
	//爆炸敌人飞机切换显示定时器
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
	//重绘
	this->onGameDraw();
}
void CPlaneApp::onKeyDown(WPARAM nKey) //按下按键, 按哪个键
{
	////玩家移动
	//if( nKey == VK_LEFT || nKey == VK_RIGHT||nKey == VK_UP||nKey == VK_DOWN)
	//{
	//	//玩家移动
	//	m_Player.PlayerMove(nKey);
	//}
	////重绘
	//this->onGameDraw();
}

//撞击敌人 敌人要掉血,子弹要删除判断是否爆炸爆炸的话, 从敌人Box里面移除, 然后移动到爆炸Box
void CPlaneApp::GunnersHitFoePlanes()//子弹撞击敌人
{
	bool bFlag = false;
	//遍历所有子弹 ,拿到一个子弹
	auto itGunner = m_GunnerBox.m_lstGunner.begin();
	while(itGunner != m_GunnerBox.m_lstGunner.end())
	{
		//遍历敌人飞机, 拿到一个敌人
		auto itFoePlane = m_FoePlaneBox.m_lstFoePlane.begin();
		while( itFoePlane != m_FoePlaneBox.m_lstFoePlane.end())
		{
			// 判断一个子弹和一个敌人是否撞在一起
			if( ( *itFoePlane)->IsHitByGunner(*itGunner ) )
			{
				bFlag = true;
				//撞击敌人 敌人要掉血,子弹要删除
				delete (*itGunner );
				(*itGunner ) = 0;
				itGunner = m_GunnerBox.m_lstGunner.erase(itGunner);

				( *itFoePlane)->BloodDown();
				//判断是否爆炸
				if( ( *itFoePlane)->IsBoom() )
				{//爆炸的话, 从敌人Box里面移除, 然后移动到爆炸Box
					if( !m_pTool)
					m_pTool = (* itFoePlane)->ToolCreate(this->m_hIns);
					// TODO: 移动到爆炸Box
					m_BlastFoePlaneBox.m_lstBlastPlane.push_back( *itFoePlane );
					itFoePlane = m_FoePlaneBox.m_lstFoePlane.erase(itFoePlane);
				}
				break;//子弹会回收, 不用继续看其他敌人
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
	//遍历所有敌人, 然后去判断每个敌人是否撞击到玩家
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
	//3.1背景移动的定时器,BACK_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,BACK_MOVE_TIMER_ID,50,0);
	//3.2玩家飞机发射炮弹定时器,PLAYER_SEND_GUNNER_TIMER_ID
	::SetTimer(this->m_hMainWnd,PLAYER_SEND_GUNNER_TIMER_ID,350,0);
	//3.3炮弹移动定时器GUNNER_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,GUNNER_MOVE_TIMER_ID,10,0);
	//3.4敌人飞机创建定时器,FOEPLANE_CREATE_TIMER_ID
	::SetTimer(this->m_hMainWnd,FOEPLANE_CREATE_TIMER_ID,1000,0);
	//3.5敌人飞机移动定时器,FOEPLANE_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,FOEPLANE_MOVE_TIMER_ID,10,0);
	//3.6爆炸敌人飞机切换显示定时器,BLAST_FOEPLANE_SHOW_TIMER_ID
	::SetTimer(this->m_hMainWnd,BLAST_FOEPLANE_SHOW_TIMER_ID,150,0);
	//3.7玩家检测按键定时器 PLAYER_MOVE_TIMER_ID
	::SetTimer(this->m_hMainWnd,PLAYER_MOVE_TIMER_ID,1,0);
	//3.8道具移动 TOOL_MOVE_TIMER_ID
	::SetTimer(m_hMainWnd , TOOL_MOVE_TIMER_ID,10,0);
}
//关闭所有定时
void CPlaneApp::KillAllTimer()
{
	//3.1背景移动的定时器,BACK_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,BACK_MOVE_TIMER_ID);
	//3.2玩家飞机发射炮弹定时器,PLAYER_SEND_GUNNER_TIMER_ID
	::KillTimer(this->m_hMainWnd,PLAYER_SEND_GUNNER_TIMER_ID);
	//3.3炮弹移动定时器GUNNER_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,GUNNER_MOVE_TIMER_ID);
	//3.4敌人飞机创建定时器,FOEPLANE_CREATE_TIMER_ID
	::KillTimer(this->m_hMainWnd,FOEPLANE_CREATE_TIMER_ID);
	//3.5敌人飞机移动定时器,FOEPLANE_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,FOEPLANE_MOVE_TIMER_ID);
	//3.6爆炸敌人飞机切换显示定时器,BLAST_FOEPLANE_SHOW_TIMER_ID
	::KillTimer(this->m_hMainWnd,BLAST_FOEPLANE_SHOW_TIMER_ID);
	//3.7玩家检测按键定时器 PLAYER_MOVE_TIMER_ID
	::KillTimer(this->m_hMainWnd,PLAYER_MOVE_TIMER_ID);
	//3.8道具移动 TOOL_MOVE_TIMER_ID
	::KillTimer(m_hMainWnd , TOOL_MOVE_TIMER_ID);
}

void CPlaneApp::ClearAllFoePlane()
{
	//遍历所有敌人, 拿到一个敌人
	auto itFoePlane = m_FoePlaneBox.m_lstFoePlane.begin();
	while( itFoePlane != m_FoePlaneBox.m_lstFoePlane.end())
	{
		if(!m_pTool)
		m_pTool = (* itFoePlane)->ToolCreate(this->m_hIns);
		//爆炸将节点移动到爆炸链表, 并从敌人box移出
		//todo: 将节点移动到爆炸链表
		m_BlastFoePlaneBox.m_lstBlastPlane.push_back( (* itFoePlane) );
		itFoePlane = m_FoePlaneBox.m_lstFoePlane.erase(itFoePlane);
	}
}