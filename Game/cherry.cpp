#include "stdafx.h"
#include "cherry.h"
#include "manager.h"

void Cherry::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_itemId = ITEM::CHERRY;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 35;
	m_info.cy = 39;

	m_Vaild = true;
	m_VaildTime = GetTickCount();

	BmpManager::GetInstance()->InsertBmp(L"../Image/133.bmp", L"133");

}

int Cherry::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Cherry::LateUpdate(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void Cherry::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"133");
	GdiTransparentBlt(dc, int((m_rect.left) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx, (int)m_info.cy, mem_dc, 0, 0, 35, 39, RGB(255, 255, 255));
}

void Cherry::Release(void)
{
}

void Cherry::SetCollision(Obj* obj, DIR::DIR _dir)
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
			DataManager::GetInstance()->AddScore(100);
			SoundManager::Get_Instance()->PlaySound(L"item.wav", SoundManager::EFFECT, 7);
			break;
		}
	}
}
