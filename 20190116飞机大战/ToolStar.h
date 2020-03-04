#pragma once
#include"ToolBase.h"
class CToolStar:public CToolBase
{
public:
	CToolStar(void);
	~CToolStar(void);

	virtual void ToolShow(HDC hMenDC)	;   
	virtual void ToolInit(HINSTANCE hIns , int x, int y)  ;

};

