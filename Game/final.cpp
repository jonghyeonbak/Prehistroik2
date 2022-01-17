#include "stdafx.h"
#include "final.h"
#include "manager.h"

Final::Final()
{
}


Final::~Final()
{
}
void Final::Initialize(void)
{
	m_dead = false;

	m_id = OBJ::OBSTACLE;
	m_obstacle_id = OBSTACLE::FINAL;
	m_dir = DIR::UP;
	m_state = STATE::IDLE;

	m_speed = 0.5f;

	m_info.cx = 32;
	m_info.cy = 54;

	m_touch = false;

	BmpManager::GetInstance()->InsertBmp(L"../Image/279.bmp", L"279");
	BmpManager::GetInstance()->InsertBmp(L"../Image/280.bmp", L"280");

}

int Final::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;
}

void Final::LateUpdate(void)
{
	
}

void Final::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();
	//HDC mMemDC = NULL;

	Rectangle(dc, m_rect.left + scroll_x, m_rect.top, m_rect.right + scroll_x, m_rect.bottom);

	if (m_touch)
	{
		HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"279");
		GdiTransparentBlt(dc, int((m_rect.left + 5) + scroll_x), int(m_rect.top + 3) + scroll_y, (int)m_info.cx - 10, (int)m_info.cy - 10, mem_dc, 0, 0, 32, 54, RGB(255, 255, 255));
	}
	else
	{
		HDC	mem_dc2 = BmpManager::GetInstance()->FindImage(L"280");
		GdiTransparentBlt(dc, int((m_rect.left + 5) + scroll_x), int(m_rect.top + 3) + scroll_y, (int)m_info.cx - 10, (int)m_info.cy - 10, mem_dc2, 0, 0, 32, 54, RGB(255, 255, 255));
	}
}
void Final::Release(void)
{
}

void Final::SetCollision(Obj* obj, DIR::DIR _dir)
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
			m_touch = true;
			//m_dead = true;
			DataManager::GetInstance()->AddScore(200);
			break;
		}
	}
}
