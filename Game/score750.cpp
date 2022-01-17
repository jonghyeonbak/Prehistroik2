#include "stdafx.h"
#include "score750.h"
#include "manager.h"

void score750::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_itemId = ITEM::SCORE750;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 48;
	m_info.cy = 18;

	m_Vaild = true;
	m_VaildTime = GetTickCount();

	BmpManager::GetInstance()->InsertBmp(L"../Image/081.bmp", L"081");

}

int score750::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void score750::LateUpdate(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void score750::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"081");
	GdiTransparentBlt(dc, int((m_rect.left ) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx, (int)m_info.cy, mem_dc, 0, 0, 48, 18, RGB(255, 255, 255));
}

void score750::Release(void)
{
}

void score750::SetCollision(Obj* obj, DIR::DIR _dir)
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
			DataManager::GetInstance()->AddScore(750);
			SoundManager::Get_Instance()->PlaySound(L"item.wav", SoundManager::EFFECT, 7);
			break;
		}
	}
}
