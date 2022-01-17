#pragma once
#ifndef BMP_MANAGER_H_
#define BMP_MANAGER_H_

#include "my_bMPmap.h"

class BmpManager
{
private:
	BmpManager();
	~BmpManager();

private:
	static	BmpManager*				m_instance;
	map<const TCHAR*, MyBmpMap*>	m_mapbit;	// 비트맵을 저장하는 맵 변수

public:
	void	InsertBmp(const TCHAR* filepath, const TCHAR* imgkey); // 이미지 삽입
	HDC		FindImage(const TCHAR* imgkey);		// 이미지 찾기
	void	Release(void);

	static	BmpManager*		GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new BmpManager;

		return m_instance;
	}

	static	void		DestroyIntance(void)
	{
		if (nullptr != m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

};

#endif // !BMP_MANAGER_H_
