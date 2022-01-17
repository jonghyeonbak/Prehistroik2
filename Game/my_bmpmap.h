#pragma once
#ifndef MY_BMPMAP_H_
#define MY_BMPMAP_H_

#include "include.h"

class MyBmpMap
{
private:
	HDC			m_mem_dc;						// dc를 저장할 변수
	HBITMAP		m_bitbmp;						// 지금 맵
	HBITMAP		m_oldmap;						// 지난 맵

public:
	MyBmpMap();
	~MyBmpMap();

public:
	HDC		GetMemDC() { return m_mem_dc; }		// dc 가져오기
	void	LoadBmp(const TCHAR* filepath);		// 비트맵 불러오기
	void	Release(void);

};

#endif // !MY_BITMAP_H_
