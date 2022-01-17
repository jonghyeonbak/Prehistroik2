#include "stdafx.h"
#include "food.h"
#include "manager.h"

void Food::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::ITEM;
	m_itemId = ITEM::FOOD;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 32;
	m_info.cy = 54;

	m_Vaild = true;
	m_VaildTime = GetTickCount();

	BmpManager::GetInstance()->InsertBmp(L"../Image/139.bmp", L"PINEAPPLE");

}

int Food::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Food::LateUpdate(void)
{
	if (m_Vaild && m_VaildTime + 200.f < GetTickCount())
	{
		m_Vaild = false;
	}
}

void Food::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"PINEAPPLE");
	GdiTransparentBlt(dc, int((m_rect.left+5) + scroll_x), int(m_rect.top+3) + scroll_y , (int)m_info.cx -10, (int)m_info.cy-10, mem_dc, 0, 0, 32, 54, RGB(255, 255, 255));
}

void Food::Release(void)
{
}

void Food::SetCollision(Obj* obj, DIR::DIR _dir)
{
	if (m_dead)
		return;

	if(obj->GetID() == OBJ::PLAYER)
	{
		switch(_dir)
		{
		case DIR::UP:
		case DIR::DOWN:
		case DIR::LEFT:
		case DIR::RIGHT:
			m_dead = true;
			DataManager::GetInstance()->AddScore(100);
			break;
		}
	}
}
