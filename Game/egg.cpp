#include "stdafx.h"
#include "egg.h"
#include "manager.h"

void Egg::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_itemId = ITEM::EGG;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 32;
	m_info.cy = 23;

	m_Vaild = true;
	m_VaildTime = GetTickCount();

	BmpManager::GetInstance()->InsertBmp(L"../Image/164.bmp", L"164");

}

int Egg::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Egg::LateUpdate(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void Egg::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"164");
	GdiTransparentBlt(dc, int((m_rect.left) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx , (int)m_info.cy, mem_dc, 0, 0, 32, 23, RGB(255, 255, 255));
}

void Egg::Release(void)
{
}

void Egg::SetCollision(Obj* obj, DIR::DIR _dir)
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
			DataManager::GetInstance()->AddScore(30);
			SoundManager::Get_Instance()->PlaySound(L"item.wav", SoundManager::EFFECT, 7);
			break;
		}
	}
}

