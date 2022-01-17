#pragma once
#ifndef MY_BMPMAP_H_
#define MY_BMPMAP_H_

#include "include.h"

class MyBmpMap
{
private:
	HDC			m_mem_dc;						// dc�� ������ ����
	HBITMAP		m_bitbmp;						// ���� ��
	HBITMAP		m_oldmap;						// ���� ��

public:
	MyBmpMap();
	~MyBmpMap();

public:
	HDC		GetMemDC() { return m_mem_dc; }		// dc ��������
	void	LoadBmp(const TCHAR* filepath);		// ��Ʈ�� �ҷ�����
	void	Release(void);

};

#endif // !MY_BITMAP_H_
