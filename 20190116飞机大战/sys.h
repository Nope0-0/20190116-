#pragma once

#include<windows.h>
#include<iostream>
#include"resource.h"
#include<list>

using namespace std;

//定时器ID
//玩家检测按键定时器
#define PLAYER_MOVE_TIMER_ID				7
//背景移动的定时器
#define BACK_MOVE_TIMER_ID					1
//玩家飞机发射炮弹定时器,
#define PLAYER_SEND_GUNNER_TIMER_ID			2
//炮弹移动定时器
#define GUNNER_MOVE_TIMER_ID				3
//敌人飞机创建定时器,
#define FOEPLANE_CREATE_TIMER_ID			4
//敌人飞机移动定时器
#define FOEPLANE_MOVE_TIMER_ID				5
//爆炸敌人飞机切换显示定时器
#define BLAST_FOEPLANE_SHOW_TIMER_ID		6

//道具移动
#define TOOL_MOVE_TIMER_ID					8

#define TOOL_MOVIE_TIMER_ID				9