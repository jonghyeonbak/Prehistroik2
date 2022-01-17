#include "stdafx.h"
#include "life.h"
#include "manager.h"

void Life::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_data_id = DATA::LIFES;


	m_info.x = 700.f;
	m_info.y = 500.f;

	m_info.cx = 50;
	m_info.cy = 50;


	BmpManager::GetInstance()->InsertBmp(L"../Image/Energy.bmp", L"Energy");


}

int Life::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Life::LateUpdate(void)
{

}

void Life::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	//HDC mMemDC = NULL;

	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Energy");
	GdiTransparentBlt(dc, int((m_rect.left+0 + scroll_x)), int(m_rect.top + 0), (int)m_info.cx, (int)m_info.cy, mem_dc, 0, 0, 50, 50, RGB(255, 255, 255));
}

void Life::Release(void)
{
}

