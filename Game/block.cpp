#include "stdafx.h"
#include "block.h"
#include "manager.h"

Block::Block()
{
}


Block::~Block()
{

}

void Block::Initialize(void)
{
	m_id = OBJ::OBSTACLE;
	m_block_id = BLOCK::DEFAULT;
	
	m_info.cx = 100.f;
	m_info.cy = 100.f;
	m_dead = false;
	m_is_invisible = false;

	BmpManager::GetInstance()->InsertBmp(L"../Image/block2.bmp", L"block2");
}

int Block::Update(void)
{
	if (true == m_dead)
		return OBJ_DEAD;

	UpdateRect();

	return OBJ_NOEVENT;

}

void Block::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();

//	Rectangle(dc, m_rect.left + scroll_x, m_rect.top + scroll_y, m_rect.right + scroll_x, m_rect.bottom + scroll_y);
	//GdiTransparentBlt(hDC, int(m_rect.left + scroll_x), int(m_rect.top), (int)m_info.cx, (int)m_info.cy, mem_dc, 0, 0, BRICK_SIZE_X, BRICK_SIZE_Y, RGB(255, 255, 255));
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"block2");
	GdiTransparentBlt(dc, int((m_rect.left) + scroll_x), int(m_rect.top) + scroll_y, (int)m_info.cx, (int)m_info.cy, mem_dc, 0, 0, 190, 210, RGB(255, 255, 255));
}


void Block::Setup(BLOCK::ID _type, bool _isInvisible)
{
	m_block_id = _type;
	m_is_invisible = _isInvisible;
}



void Block::SetCollision(Obj* obj, DIR::DIR _dir)
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
			//DataManager::GetInstance()->AddScore(10);
			break;
		}
	}
}