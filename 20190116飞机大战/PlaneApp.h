#pragma once
#include"gameapp.h"
#include"sys.h"
#include"Back.h"
#include"Player.h"
#include"GunnerBox.h"
#include"FoePlaneBox.h"
#include"BlastFoePlaneBox.h"
#include"ToolBase.h"
#include"ToolMovie.h"
class CPlaneApp :
	public CGameApp
{
public:
	// ============= 绘图资源===============
		//获得窗口对应的DC
	HDC hdc ;
	//创建兼容DC 
	HDC hMenDC ;
	//创建兼容位图
	HBITMAP hMenBmp;

	// ============= 绘图资源===============
	CBack m_Back;
	CPlayer m_Player;
	CGunnerBox m_GunnerBox;
	CFoePlaneBox m_FoePlaneBox;
	CBlastFoePlaneBox m_BlastFoePlaneBox;
	CToolBase * m_pTool ; 
	CToolMovie m_ToolMovie;
public:
	CPlaneApp(void);
	~CPlaneApp(void);

	virtual void onGameCreate()override; //游戏创建,包含初始化,加载位图 :实例句柄 HINSTANCE
	virtual void onGameDraw()override; //绘图HDC GetDC() 传入窗口句柄: 窗口句柄
	virtual void onGameRun( WPARAM nTimerID)override; //定时器, 哪个定时器
	virtual void onKeyDown(WPARAM nKey)override; //按下按键, 按哪个键
	void GunnersHitFoePlanes();//子弹撞击敌人
	bool IsGameOver();//是否游戏结束
	void SetAllTimer();//开启所有定时
	void KillAllTimer();//关闭所有定时
	void ClearAllFoePlane();
};


//飞机大战 过程 
//1.创建项目 , win32项目 , 类向导添加CPlaneApp , 找到游戏壳子, 然后打开工程目录, 粘贴在目录下, 右键添加现有项, 将文件选中,添加入项目
//2.修改字符集 , 多字节 , 要完成游戏壳的链接 写CREATE(CPlaneApp)宏
//3.添加资源 , 右键打开工程目录, 将飞机图片资源, 放在工程同级的目录下. 添加位图, 修改位图对应的宏(双击.rc文件, 在资源视图下查看)
//4.工程中有很多头文件和宏要使用, 我们申请一个公共的.sys.h放很多头文件和宏

//5.根据流程以及类图, 来写注释 , 包含sys.h
//6.写背景的类, 类向导添加CBack , 包含sys.h , 实体类共有的属性和方法, 实现的时候注意 类名:: 函数名 ,构造初始化成员
//析构 回收位图, init 需要宏 包含resource.h , 在sys.h中添加头包含 
// 窗口大小调整
// 使用背景类, 1. 定义背景对象成员(包含头文件) 2. Create里初始化 打开定时器 3. Draw里显示 4.Run里 移动

//7.写玩家类 类向导添加CPlayer 包含sys.h 实体类共有的属性和方法 实现的时候注意 类名:: 函数名 ,构造初始化成员
//在app里使用玩家类 1. 定义玩家对象成员(包含头文件) 2. Create里初始化 3. Draw里显示 4. 移动
//7.1 问题: 显示有背景 白色  去除图片背景颜色  SRCAND
//7.2 问题: 移动过程中, 比较卡顿, 反应迟钝 , 采取按键响应来完成移动的.
//使用消息, 消息有一定的灵敏度的, 消息的传发有间隔的 50ms--> 响应的不及时   假如50ms发了10次 , 他响应了1次
//解决办法  减少间隔和延时. 消息是系统转发的, 没法改. --> 采取定时器的方法, 在定时器里检测按键
// 添加玩家按键检测定时器 //检测玩家按键 使用函数  ::GetAsyncKeyState(); //异步检测按键状态 ,如果按了某个键, 返回一个true

//问题:闪屏  原因是,图片一会有一会没有,就会闪; 
//贴图片有先后顺序, 窗口显示图片有周期的, 很多图片在一个周期显示, 和不在一个周期显示, 会造成, 图片一会又一会没有, 那么就会闪屏
//解决办法: 贴图片没有先后顺序 , 采用的方法是双缓冲
//双缓冲 创建最终DC的兼容DC, 在兼容DC上绘图, 实体对象创建兼容DC的兼容DC绘图, 然后一次完成兼容DC向最终DC的绘图
//注意 : 实体类调用参数时是最终DC的兼容DC 比如: m_Back.BackShow(hMenDC);  而非hdc
//onGameDraw 反复调用, 反复创建销毁资源, 会导致卡顿, 把资源编程成员变量.Create里面写初始化, 析构里回收

//8. 写子弹的类, 包含sys.h , 从类图拿到成员, 按照实体类的写法去写
// 写子弹盒子的类,包含sys.h ,sys.h添加list包含, 析构里面回收聚合对象, 移动超出边界, 回收对象(每次操作一个节点), 显示可以使用范围for
// 写玩家飞机发射炮弹函数 , 1. new 炮弹对象 2. 炮弹初始化 3. 加到Box里管理
// App里面定义子弹Box , 包含头文件定义对象成员 , Create里开启 发射炮弹定时器, 开启炮弹移动定时, Draw里 写炮弹显示,Run 写发射炮弹, 炮弹移动

//9. 敌人飞机  ShowID的问题, 链表操作飞机操作要统一, 爆炸回收对象要统一ShowID , 所以采用 ShowID 减的方式, 初始非0
// 先写父类 , 先实现非虚函数 构造给初值 然后写三种子类, 写一个其他粘贴 , 构造给出随机坐标, Show 给出根据ID显示
// 写飞机的盒子, 其他的与子弹盒子一样, 在创建时 需要随机数
// 使用敌人飞机盒子  :在App里创建Box , Create打开定时器 2个  Draw 写显示, Run里面写 创建和移动

//10.//判断子弹是否撞到敌人 判断图片大小范围  子弹移动 撞击敌人 敌人要掉血,子弹要删除判断是否爆炸爆炸的话, 从敌人Box里面移除, 然后移动到爆炸Box
//// TODO: 移动到爆炸Box
//使用一下  添加子弹撞敌人 在子弹移动位置添加函数 GunnersHitFoePlanes

//11. 显示爆炸  写爆炸盒子
// 显示跟其他一样  切换显示 : 定时将ShowID-- , ShowID= 0 ; 回收
// 使用爆炸盒子 定义对象成员 

//12. 敌人飞机撞玩家飞机 重写IsHitPlayer()  以及在App中完成IsGameOver()
//敌人移动的地方添加 是否游戏结束判断, 将SetTimer 和KillTimer 封装 // 游戏结束, 关闭所有定时器, 发送退出消息