#include "stdafx.h"
#include "obj.h"


Obj::Obj()
	:m_dead(false), m_speed(0.f), m_draw_id(0), m_frame_key(nullptr)
{
	ZeroMemory(&m_info, sizeof(m_info));    // info 초기화
	ZeroMemory(&m_rect, sizeof(m_rect));	// rect 초기화
	ZeroMemory(&m_frame, sizeof(FRAME));
}


Obj::~Obj()
{
}

void Obj::SetPos(float x_, float y_)		// 물체 좌표 세팅
{
	m_info.x = x_;
	m_info.y = y_;
}

void Obj::UpdateRect(void)					// info를 rect로 대입 + 복사
{
	m_rect.left = long(m_info.x - (m_info.cx * 0.5f));
	m_rect.right = long(m_info.x + (m_info.cx * 0.5f));
	m_rect.top = long(m_info.y - (m_info.cy * 0.5f));
	m_rect.bottom = long(m_info.y + (m_info.cy * 0.5f));
}

void Obj::SetFrameKey(TCHAR* pFrameKey)
{
	m_frame_key = pFrameKey;
}

void Obj::SetDirection(DIR::DIR dir)
{
	m_dir = dir;
}

void Obj::SetDrawID(int _iDrawID)
{
	m_draw_id = _iDrawID;
}

void Obj::MoveFrame(void)												// 프레임 움직이는 함수
{
	if (m_frame.frame_time + m_frame.frame_speed < GetTickCount())
	{
		++m_frame.frame_start;
		m_frame.frame_time = GetTickCount();

		if (m_frame.frame_start > m_frame.frame_end)
			m_frame.frame_start = 0;
	}
}

void Obj::SetPosX(float x_)
{
	m_info.x += x_;
}

void Obj::SetPosY(float y_)
{
	m_info.y += y_;
}