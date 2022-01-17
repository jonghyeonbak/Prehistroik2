#include "stdafx.h"
#include "scroll_manager.h"
#include "key_manager.h"


float		ScrollManager::m_scroll_x = 0.f;
float		ScrollManager::m_scroll_y = 0.f;
ScrollManager* ScrollManager::m_instance = nullptr;

ScrollManager::ScrollManager()
{
}


ScrollManager::~ScrollManager()
{
	Release();
}

void ScrollManager::Update()
{

}

void ScrollManager::Late_Update(void)
{
}

void ScrollManager::Release(void)
{
	InitScrollX(0);
	InitScrollY(0);
}
void ScrollManager::ScrollLock(void)			// ��ũ���� ���ϴ� ���� �̻����� �� ����� �ϴ� �Լ�
{
	if (0 < m_scroll_x)							// x ��ũ���� 0���� ũ�� 
		m_scroll_x = 0.f;	
	// 0���� �ʱ�ȭ
	else if (m_scroll_x > 4096)
		m_scroll_x = 4096.f;
		
	// �Ѹ���� x��ǥ�� �� �̻� �� ����� ����.
	if (0 < m_scroll_y)
		m_scroll_y = 0.f;
	else if (m_scroll_y > 1360)
		m_scroll_y = 1360.f;
	//if (WINCY - TILEY * TILECY > m_scroll_y)
	//	m_scroll_y = WINCY - TILEY * TILECY;
}

void ScrollManager::SetScrollY3(float y_)
{
	if (0 < m_scroll_y)
		m_scroll_y = 0.f;

	else if (m_scroll_y > 1360)
		m_scroll_y = 1360.f;
}