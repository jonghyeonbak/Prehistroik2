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
	map<const TCHAR*, MyBmpMap*>	m_mapbit;	// ��Ʈ���� �����ϴ� �� ����

public:
	void	InsertBmp(const TCHAR* filepath, const TCHAR* imgkey); // �̹��� ����
	HDC		FindImage(const TCHAR* imgkey);		// �̹��� ã��
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
