#pragma once
#include"TooLBase.h"
class CToolBoom:public CToolBase
{
public:
	CToolBoom(void);
	~CToolBoom(void);

	virtual void ToolShow(HDC hMenDC)	;   
	virtual void ToolInit(HINSTANCE hIns , int x, int y)  ;

};

