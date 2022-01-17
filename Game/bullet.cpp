#include "stdafx.h"
#include "bullet.h"
#include "manager.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
void Bullet::Initialize(void)
{
	m_id = OBJ::BULLET;
	m_dir = DIR::RIGHT;

	m_info.cx = 60.f;
	m_info.cy = 60.f;

	m_speed = 10.f;

	m_dead = false;

	parent_id = OBJ::PLAYER;

	BmpManager::GetInstance()->InsertBmp(L"../Image/22.bmp", L"22");
	BmpManager::GetInstance()->InsertBmp(L"../Image/22_2.bmp", L"22_2");

	/*BmpManager::GetInstance()->InsertBmp(L"../Image/068.bmp", L"68");
	BmpManager::GetInstance()->InsertBmp(L"../Image/069.bmp", L"69");
	BmpManager::GetInstance()->InsertBmp(L"../Image/070.bmp", L"70");*/

	m_frame_key = L"22";

	m_pre_state = STATE::IDLE;
	m_cur_state = STATE::IDLE;

	m_frame.frame_start = 0;
	m_frame.frame_end = 2;
	m_frame.frame_scene = 0;
	m_frame.frame_speed = 100;
	m_frame.frame_time = GetTickCount();
}

int Bullet::Update(void)
{
	if (m_dead)
		return OBJ_DEAD;

	//switch (m_dir)
	//{
	//case DIR::RIGHT:
	//	m_frame_key = L"22";
		m_info.x += m_speed;
	//	break;
	//case DIR::LEFT:
	//	//m_frame_key = L"22_2";
	//	m_info.x -= m_speed;
	//	break;

	//}

	//StateChange();
	MoveFrame();
	UpdateRect();

	return OBJ_NOEVENT;

}

void Bullet::LateUpdate(void)
{
}

void Bullet::Render(HDC dc)
{
	//HDC mem_dc = NULL;
	/*switch (m_AnimNum)
	{
	case 0:
		mem_dc = BmpManager::GetInstance()->FindImage(L"68");
		if (m_AnimTime + 100.f < GetTickCount())
		{
			++m_AnimNum;
			m_AnimTime = GetTickCount();
		}
		break;
	case 1:
		mem_dc = BmpManager::GetInstance()->FindImage(L"69");
		if (m_AnimTime + 100.f < GetTickCount())
		{
			++m_AnimNum;
			m_AnimTime = GetTickCount();
		}
		break;
	case 2:
		mem_dc = BmpManager::GetInstance()->FindImage(L"70");
		if (m_AnimTime + 100.f < GetTickCount())
		{
			++m_AnimNum;
			m_AnimTime = GetTickCount();
		}
		break;
	}*/

	int scroll_x = (int)ScrollManager::GetInstance()->GetScrollX();
	int scroll_y = (int)ScrollManager::GetInstance()->GetScrollY();
	//Rectangle(dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	HDC mem_dc = BmpManager::GetInstance()->FindImage(m_frame_key);

	GdiTransparentBlt(dc,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_rect.left + scroll_x),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_rect.top  + scroll_y),
		(int)m_info.cx,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_info.cy,
		mem_dc,							// ��Ʈ�� ������ ������ �ִ� DC
		m_frame.frame_start * (int)m_info.cx,								// 7,8���� ��Ʈ���� ����� ������ǥ
		m_frame.frame_scene * (int)m_info.cy,
		60,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		60,
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

void Bullet::Release(void)
{

}

void Bullet::SetCollision(Obj* obj, DIR::DIR _eDIR)
{
	if (obj->GetID() == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		default:
			m_dead = true;
			break;
		}
	}
}
