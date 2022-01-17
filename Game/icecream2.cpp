#include "stdafx.h"
#include "icecream2.h"
#include "manager.h"

void Icecream2::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_itemId = ITEM::ICECREAM2;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 30;
	m_info.cy = 53;

	m_Vaild = true;
	m_VaildTime = GetTickCount();

	BmpManager::GetInstance()->InsertBmp(L"../Image/153.bmp", L"153");

}

int Icecream2::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Icecream2::LateUpdate(void)
{
}

void Icecream2::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"153");
	GdiTransparentBlt(dc,
		int((m_rect.left + 5) + scroll_x),
		int(m_rect.top + 3) + scroll_y,
		(int)m_info.cx,
		(int)m_info.cy,
		mem_dc, 0, 0, 30, 53, RGB(255, 255, 255));
}

void Icecream2::Release(void)
{
}

void Icecream2::SetCollision(Obj* obj, DIR::DIR _dir)
{
	if (m_dead)
		return;

	if (obj->GetID() == OBJ::PLAYER)
	{
		switch (_dir)
		{
		case DIR::UP:
		case DIR::DOWN:
		case DIR::LEFT:
		case DIR::RIGHT:
			m_dead = true;
			DataManager::GetInstance()->AddScore(800);
			SoundManager::Get_Instance()->PlaySound(L"item.wav", SoundManager::EFFECT, 7);
			break;
		}
	}
}
