#include "stdafx.h"
#include "key_manager.h"

KeyManager*  KeyManager::m_instance = nullptr;

KeyManager::KeyManager()
{
	ZeroMemory(m_keystate, sizeof(m_keystate));
}

KeyManager::~KeyManager()
{
}

bool KeyManager::KeyPressing(int key_)   // Ű�� ��� ������ ���� ��
{
	if (GetAsyncKeyState(key_) & 0x8000) // Ű�� �����ִٸ� true ��ȯ
		return true;

	return false;
}

bool KeyManager::KeyDown(int key_)
{
	// ������ ������ �����鼭,  ���� Ű�� ������ ��
	if (!m_keystate[key_] && (GetAsyncKeyState(key_) & 0x8000))
	{
		// Ű ���¿� ������ ���� ���¸� ���� �� true ��ȯ
		m_keystate[key_] = !m_keystate[key_];
		return true;
	}
	// ������ ��������, ���� ������ �ʰ� ���� ��
	if (m_keystate[key_] && !(GetAsyncKeyState(key_) & 0x8000))
		// Ű ���¿� ������ ���� ���¸� ����
		m_keystate[key_] = !m_keystate[key_];

	//false ��ȯ
	return false;
}

bool KeyManager::KeyUp(int key_)
{
	// ������ ��������, ���� ������ ���� ������ ��
	if (m_keystate[key_] && !(GetAsyncKeyState(key_) & 0x8000))
	{
		// Ű ���¿� ������ ���� ���¸� ���� �� true ��ȯ
		m_keystate[key_] = !m_keystate[key_];
		return true;
	}
	// ������ ������ �����鼭, ���� Ű�� ������ ��
	if (!m_keystate[key_] && (GetAsyncKeyState(key_) & 0x8000))
		// Ű ���¿� ������ ���� ���¸� ����
		m_keystate[key_] = !m_keystate[key_];

	return false;
}
