#pragma once

#ifndef KEY_MANAGER_H_
#define KEY_MANAGER_H_

#include "include.h"

class KeyManager
{
private:
	static KeyManager*	m_instance;
	bool				m_keystate[VK_MAX];		// Ű�� �ƽ����� �ƴ��� Ȯ��

private:
	KeyManager();
	~KeyManager();

public:
	bool	KeyPressing(int key_);
	bool	KeyDown(int key_);
	bool	KeyUp(int key_);

public:
	static	KeyManager*		GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new KeyManager;

		return m_instance;
	}

	static void	DestroyInstance(void)
	{
		if (nullptr != m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};


#endif // !KEYMANAGER_H_
