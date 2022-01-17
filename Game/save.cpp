#include "stdafx.h"
#include "save.h"
#include "manager.h"

Save::Save()
{
}


Save::~Save()
{
}

void Save::Initialize(void)
{
	m_id = OBJ::OBSTACLE;
	m_block_id = OBSTACLE::SAVE;

	m_info.cx = 50.f;
	m_info.cy = 50.f;
	m_dead = false;
	m_is_invisible = false;
	m_crush = false;

	BmpManager::GetInstance()->InsertBmp(L"../Image/281.bmp", L"281");
	BmpManager::GetInstance()->InsertBmp(L"../Image/282.bmp", L"282");
}

int Save::Update(void)
{
	if (true == m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;

}

void Save::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();

	
		if (m_crush)
		{
		HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"281");
		GdiTransparentBlt(dc, int((m_rect.left) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx *2, (int)m_info.cy*2, mem_dc, 0, 0, 50, 50, RGB(255, 255, 255));
		}
		else
		{
		HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"282");
		GdiTransparentBlt(dc, int((m_rect.left) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx*2, (int)m_info.cy*2, mem_dc, 0, 0, 50, 50, RGB(255, 255, 255));
		}
}


void Save::Setup(OBSTACLE::ID _type, bool _isInvisible)
{
	m_block_id = _type;
	m_is_invisible = _isInvisible;
}



void Save::SetCollision(Obj* obj, DIR::DIR _dir)
{
	if (m_dead)
		return;

	if (obj->GetID() == OBJ::PLAYER)
	{
		switch (_dir)
		{
		case DIR::UP:
		case DIR::LEFT:
		case DIR::RIGHT:
		case DIR::DOWN:
			m_crush = true;
			break;
		}
	}
}