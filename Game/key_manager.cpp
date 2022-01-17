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

bool KeyManager::KeyPressing(int key_)   // 키를 계속 누르고 있을 때
{
	if (GetAsyncKeyState(key_) & 0x8000) // 키가 눌려있다면 true 반환
		return true;

	return false;
}

bool KeyManager::KeyDown(int key_)
{
	// 이전에 눌림이 없으면서,  현재 키를 눌렀을 때
	if (!m_keystate[key_] && (GetAsyncKeyState(key_) & 0x8000))
	{
		// 키 상태에 눌리지 않은 상태를 대입 후 true 반환
		m_keystate[key_] = !m_keystate[key_];
		return true;
	}
	// 이전에 눌렀으며, 현재 누르지 않고 있을 때
	if (m_keystate[key_] && !(GetAsyncKeyState(key_) & 0x8000))
		// 키 상태에 눌리지 않은 상태를 대입
		m_keystate[key_] = !m_keystate[key_];

	//false 반환
	return false;
}

bool KeyManager::KeyUp(int key_)
{
	// 이전에 눌렸으며, 현재 눌리지 않은 상태일 때
	if (m_keystate[key_] && !(GetAsyncKeyState(key_) & 0x8000))
	{
		// 키 상태에 눌리지 않은 상태를 대입 후 true 반환
		m_keystate[key_] = !m_keystate[key_];
		return true;
	}
	// 이전에 눌림이 없으면서, 현재 키를 눌렀을 때
	if (!m_keystate[key_] && (GetAsyncKeyState(key_) & 0x8000))
		// 키 상태에 눌리지 않은 상태를 대입
		m_keystate[key_] = !m_keystate[key_];

	return false;
}
