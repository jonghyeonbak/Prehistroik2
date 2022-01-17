#include "stdafx.h"
#include "dog.h"
#include "manager.h"

Dog::Dog()
{
}


Dog::~Dog()
{
}

void Dog::Initialize(void)
{
	m_id = OBJ::MONSTER;
	m_monster_id = MONSTER::DOG;

	m_info.cx = 70.f;
	m_info.cy = 50.f;

	m_speed = 2.5f;

	m_time = 10.f;
	m_jump = false;
	m_jump_power = 50.f;
	m_jump_y = 0.f;
	//m_bMove = false;

	m_dir = DIR::LEFT;
	//m_State = STATE::IDLE;

	is_vaild = true;
	m_vaild_time = GetTickCount();
	cool_time = 0.f;

	m_die = false;

	//move = true;

	BmpManager::GetInstance()->InsertBmp(L"../Image/398.bmp", L"398");
	BmpManager::GetInstance()->InsertBmp(L"../Image/401.bmp", L"401");
	BmpManager::GetInstance()->InsertBmp(L"../Image/402.bmp", L"402");



	//m_frame_key = L"315";

	//m_pre_state = STATE::IDLE;
	m_cur_state = STATE::IDLE;

	//m_frame.frame_start = 0;
	//m_frame.frame_end = 1;
	//m_frame.frame_scene = 0;
	//m_frame.frame_speed = 200;
	//m_frame.frame_time = GetTickCount();
}


int Dog::Update(void)
{
	if (m_dead)
	{
		//m_info.y += FALL_DOWN;
		/*if (m_info.y >= WINCY)
		{*/
		m_cur_state = STATE::DEAD;

		if (m_die_time + 2000.f < GetTickCount())
		{
			m_die_time = GetTickCount();
			m_die = !m_die;
		}
		return OBJ_DEAD;

		/*	}
		UpdateRect();
		return OBJ_NOEVENT;*/
	}

	/*if (m_bMove)
	{*/
	//float		y = 0.f;
	////bool		line_col = LineManager::GetInstance()->CollisionLine(m_info.x, m_info.y, &y);
	/*m_jump_y = m_info.y;
	m_jump = true;

	m_time = GetTickCount();*/
//	m_info.x -= m_speed;

	if (move)
	{
		m_info.x -= m_speed;
		if (m_time + 1000 <= GetTickCount()) // 3초에 한번 씩 수행
		{
			m_jump_y = m_info.y;	// jump_y에 플레이어 y좌표를 대입
			m_jump = true;	// false 에서 true로 변환
			
			m_time = GetTickCount();
		}
		//m_frame_key = L"Dino";
		//m_cur_state = STATE::WALK;

		//if (line_col)
		//	m_info.y = y - (m_info.cy * 0.5f);

		Jumping();
	}
	else
		CheckStartMove();

	StateChange();
	UpdateRect();

	return OBJ_NOEVENT;
}

void Dog::Jumping(void)
{
	if (m_dead)
		return;

	float		y = 0.f;
	bool		line_col = LineManager::GetInstance()->CollisionLine(m_info.x, m_info.y, &y);

	if (m_jump)
	{
		m_info.y = m_jump_y - (m_jump_power * m_time - 9.8f * m_time * m_time * 0.5f);
		m_time += 0.2f;
		m_cur_state = STATE::JUMP;

		if (line_col && y + 10 < m_info.y + (m_info.cy * 0.5f))
		{
			m_jump = false;
			m_time = 0.f;
			m_info.y = y - (m_info.cy * 0.5f);
			m_cur_state = STATE::IDLE;

		}
	}
	else if (line_col)
		m_info.y = y - (m_info.cy * 0.5f);
	//else
	//{
	//	//m_speed *= -1.f;
	//	//m_dir = DIR::LEFT ? DIR::RIGHT : DIR::LEFT;
	//}
}

void Dog::LateUpdate(void)
{

}

void Dog::Render(HDC dc)
{
	float scroll_x = ScrollManager::GetInstance()->GetScrollX();
	float scroll_y = ScrollManager::GetInstance()->GetScrollY();

	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top + scroll_y, m_rect.right + scroll_x, m_rect.bottom + scroll_y);

	HDC	mem_dc = NULL;

	if (m_walk)
	{

		mem_dc = BmpManager::GetInstance()->FindImage(L"398");
		if (m_walktime + 150.f < GetTickCount())
		{
			m_walktime = GetTickCount();
			m_walk = !m_walk;
		}
		
	}
	else
	{

		mem_dc = BmpManager::GetInstance()->FindImage(L"401");
		if (m_walktime + 150.f < GetTickCount())
		{
			m_walktime = GetTickCount();
			m_walk = !m_walk;
		}
		
	}

	if (m_dead)
	{
		mem_dc = BmpManager::GetInstance()->FindImage(L"402");
	}
	//GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 32, 32, RGB(255, 255, 255));

	GdiTransparentBlt(dc, int((m_rect.left-10) + scroll_x),
		int(m_rect.top-35) + scroll_y,
		(int)m_info.cx+20,
		(int)m_info.cy+20,
		mem_dc,
		0,
		0,
		70,
		50,
		RGB(255, 255, 255));
}

void Dog::Release(void)
{

}

void Dog::SetVaild()
{
	if (is_vaild && m_vaild_time + cool_time < GetTickCount())
	{
		m_vaild_time = GetTickCount();
		is_vaild = false;
	}
}

void Dog::SetCollision(Obj* obj, DIR::DIR dir_)
{
	if (m_dead)
		return;

	if (obj->GetID() == OBJ::PLAYER)
	{
		switch (dir_)
		{
		case DIR::UP:
			if (ObjManager::GetInstance()->GetPlayerVaild() == !is_vaild)
			{
				m_dead = true;
				DataManager::GetInstance()->AddScore(100);
			}
			else
				break;
		case DIR::LEFT:
		case DIR::RIGHT:
			break;
		default:
			break;
		}
	}
	if (obj->GetID() == OBJ::BULLET)
	{
		switch (dir_)
		{
		default:
			m_dead = true;
			DataManager::GetInstance()->AddScore(500);
			break;
		}
	}
}
void Dog::StateChange()
{
	/*if (m_pre_state != m_cur_state)
	{
	switch (m_cur_state)
	{
	case STATE::IDLE:
	m_frame.frame_start = 0;
	m_frame.frame_end = 2;
	m_frame.frame_scene = 0;
	m_frame.frame_speed = 200;
	m_frame.frame_time = GetTickCount();
	break;

	case STATE::WALK:
	m_frame.frame_start = 0;
	m_frame.frame_end = 2;
	m_frame.frame_scene = 0;
	m_frame.frame_speed = 200;
	m_frame.frame_time = GetTickCount();
	break;

	case STATE::JUMP:
	m_frame.frame_start = 0;
	m_frame.frame_end = 2;
	m_frame.frame_scene = 3;
	m_frame.frame_speed = 185;
	m_frame.frame_time = GetTickCount();
	break;

	case STATE::ATTACK:
	m_frame_key = L"Weapons_R";
	m_frame.frame_start = 0;
	m_frame.frame_end = 6;
	m_frame.frame_scene = 0;
	m_frame.frame_speed = 185;
	m_frame.frame_time = GetTickCount();
	break;

	case STATE::HIT:
	break;

	case STATE::DEAD:
	m_frame.frame_start = 0;
	m_frame.frame_end = 4;
	m_frame.frame_scene = 0;
	m_frame.frame_speed = 100;
	m_frame.frame_time = GetTickCount();
	break;
	}

	m_pre_state = m_cur_state;
	}*/
}
//void Monster::Check_StartMove()
//{
//	if (!m_bMove)
//	{
//		float distance = m_tInfo.fX - CObjMgr::Get_Instance()->Get_Player_RECT().left;
//		if (distance < 700.f)
//			m_bMove = true;
//		/*else if (distance > - 500.f)
//		{
//		m_bDead = true;
//		}*/
//	}
//
//}
//
