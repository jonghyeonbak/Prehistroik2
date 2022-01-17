#include "stdafx.h"
#include "obj.h"


Obj::Obj()
	:m_dead(false), m_speed(0.f), m_draw_id(0), m_frame_key(nullptr)
{
	ZeroMemory(&m_info, sizeof(m_info));    // info �ʱ�ȭ
	ZeroMemory(&m_rect, sizeof(m_rect));	// rect �ʱ�ȭ
	ZeroMemory(&m_frame, sizeof(FRAME));
}


Obj::~Obj()
{
}

void Obj::SetPos(float x_, float y_)		// ��ü ��ǥ ����
{
	m_info.x = x_;
	m_info.y = y_;
}

void Obj::UpdateRect(void)					// info�� rect�� ���� + ����
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

void Obj::MoveFrame(void)												// ������ �����̴� �Լ�
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