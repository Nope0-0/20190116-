#pragma once
#include"sys.h"
class CToolMovie
{
public:
	bool		m_bFlag ;
	HBITMAP		m_hBmpMovie[5];
	int			m_nX;
	int			m_nY;
	int			m_nIndex;
public:
	CToolMovie(void);
	~CToolMovie(void);

	void ToolMovieInit(HINSTANCE hIns);
	void ToolMovieShow(HDC hMenDC);

};

