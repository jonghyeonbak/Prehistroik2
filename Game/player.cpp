#include "stdafx.h"
#include "player.h"
#include "abstractfactory.h"
#include "manager.h"



Player::Player()
{
}


Player::~Player()
{
	Release();
}

void Player::KeyInput(void)
{
	if (m_dead)
		return;


	if (KeyManager::GetInstance()->KeyPressing(VK_LEFT)) 
	{
		float x = m_info.x - m_speed;
		float y = m_info.y - m_speed;

		if (x > 30 )
		{
			m_info.x -= m_speed;
			if (m_info.x > 200)
				ScrollManager::GetInstance()->SetScrollX(+m_speed);

		/*if (m_info.y < 730)
			ScrollManager::GetInstance()->SetScrollY(+2.f);*/
		
		}
		
		m_frame_key = L"Player_L";
		m_cur_state = STATE::WALK;
		m_dir = DIR::LEFT;

		if (KeyManager::GetInstance()->KeyDown(VK_UP))
		{
			SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
			SoundManager::Get_Instance()->PlaySound(L"jump.wav", SoundManager::EFFECT, 7);
			if (!m_jump)
			{

				m_jump_y = m_info.y;	// jump_y에 플레이어 y좌표를 대입
				m_jump = true;			// false 에서 true로 변환
			}
			m_cur_state = STATE::JUMP;
		}
		else if (KeyManager::GetInstance()->KeyDown(VK_SPACE))
		{
			/*int scroll_x = (int)ScrollManager::GetInstance()->GetScrollX();
			int scroll_y = (int)ScrollManager::GetInstance()->GetScrollY();*/
			SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
			SoundManager::Get_Instance()->PlaySound(L"attack.wav", SoundManager::EFFECT, 7);
			ObjPoolManager::GetInstance()->SpawnBullet(BULLET::HAMMER, m_info.x, m_info.y, m_dir = DIR::RIGHT);

			//m_frame_key = L"Player_RIGHT";
			m_cur_state = STATE::ATTACK;

		}
	}
	
	else if (KeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		m_info.x += m_speed;

		m_frame_key = L"Player_R";
		m_cur_state = STATE::WALK;

		if (KeyManager::GetInstance()->KeyDown(VK_UP))
		{
			if (!m_jump)
			{
				m_jump_y = m_info.y;	// jump_y에 플레이어 y좌표를 대입
				m_jump = true;			// false 에서 true로 변환
			}
			m_cur_state = STATE::JUMP;
			SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
			SoundManager::Get_Instance()->PlaySound(L"jump.wav", SoundManager::EFFECT, 7);
		}

	}
	
	else if (KeyManager::GetInstance()->KeyDown(VK_UP))
	{
		if (m_info.y < 200)
			ScrollManager::GetInstance()->SetScrollY(+10.f);


		m_cur_state = STATE::JUMP;
		if (!m_jump)
		{	
			m_jump_y = m_info.y;	// jump_y에 플레이어 y좌표를 대입
			m_jump = true;			// false 에서 true로 변환
			SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
		SoundManager::Get_Instance()->PlaySound(L"jump.wav", SoundManager::EFFECT, 7);

		}
		/*m_frame_key = L"Player_R";*/
		else if (KeyManager::GetInstance()->KeyDown(VK_SPACE))
		{
			SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
			SoundManager::Get_Instance()->PlaySound(L"attack.wav", SoundManager::EFFECT, 7);
			int scroll_x = (int)ScrollManager::GetInstance()->GetScrollX();
			int scroll_y = (int)ScrollManager::GetInstance()->GetScrollY();

			ObjPoolManager::GetInstance()->SpawnBullet(BULLET::HAMMER, m_info.x + (int)ScrollManager::GetInstance()->GetScrollX() , m_info.y + (int)ScrollManager::GetInstance()->GetScrollY(), m_dir = DIR::RIGHT);

			//m_frame_key = L"Player_RIGHT";
			m_cur_state = STATE::ATTACK;
		
		}

	}

	else if (KeyManager::GetInstance()->KeyDown(VK_SPACE))
	{
		int scroll_x = (int)ScrollManager::GetInstance()->GetScrollX();
		int scroll_y = (int)ScrollManager::GetInstance()->GetScrollY();

		SoundManager::Get_Instance()->StopSound(SoundManager::CHANNELID::EFFECT);
     	SoundManager::Get_Instance()->PlaySound(L"attack.wav", SoundManager::EFFECT, 7);

		if (m_attack)
		{
			m_frame.frame_start = 1;
			m_frame.frame_end = 1;
			m_frame.frame_scene = 4;
			m_frame.frame_speed = 150;

			if (m_attack_time + 300.f < GetTickCount())
			{
				m_attack_time = GetTickCount();
				m_attack = !m_attack;
			}
		}
		else
		{
			m_frame.frame_start = 2;
			m_frame.frame_end = 2;
			m_frame.frame_scene = 4;
			m_frame.frame_speed = 150;

			if (m_attack_time + 300.f < GetTickCount())
			{
				m_attack_time = GetTickCount();
				m_attack = !m_attack;
			}
		}
		
		ObjPoolManager::GetInstance()->SpawnBullet(BULLET::HAMMER, m_info.x , m_info.y, m_dir);
		
		
		//m_frame_key = L"Player_RIGHT";
		m_cur_state = STATE::ATTACK;
		//m_attack = true;
	}
	
	else
		m_cur_state = STATE::IDLE;

		if (KeyManager::GetInstance()->KeyDown('9'))
		{
			g_fSound += 0.1f;

			if (g_fSound > 1.f)
				g_fSound = 1.f;

			SoundManager::Get_Instance()->SetChannelVolume(SoundManager::EFFECT, 7);
			return;
		}

		if (KeyManager::GetInstance()->KeyDown('0'))
		{
			g_fSound -= 0.1f;

			if (g_fSound < 0.f)
				g_fSound = 0.f;

			SoundManager::Get_Instance()->SetChannelVolume(SoundManager::EFFECT, 7);
			return;
		}
}

void Player::Jumping(void)
{

	if (m_dead)
		return;

	float		y = 0.f;
					// 점프 했을 때 두 직선 사이에 있으면 TRUE
	bool		line_col = LineManager::GetInstance()->CollisionLine(m_info.x, m_info.y, &y);

	if (true == m_jump)  // jump 가 true 라면
	{
		// 플레이어 y = jump_y - ( (v*sin.seta *time) - 1/2 g*(t제곱))
			// y =  y - ((속력(힘)*시간) - 1/2 중력가속도*(시간의 제곱) ) 
		m_info.y = m_jump_y - (m_jump_power * m_time - 9.8f * m_time * m_time * 0.5f); // y 구하는 공식 
		m_time += 0.2f;			// 시간 0.2f 증가
		m_cur_state = STATE::JUMP;



		// 두 직선 사이에 플레이어가 있고, 점프한 상태의 플레이어 y보다 (플레이어 y좌표 + (플레이어 사이즈의 반))이 더 크다면
		if (line_col && y < m_info.y + (m_info.cy * 0.5f))
		{
			m_jump = false;						// jump 는 false
			m_time = 0.f;						// time 0 초기화
			m_info.y = y - (m_info.cy * 0.5f);	// 플레이어 y = y - (플레이어 사이즈의 반)
		}

	}
	else if (line_col) // 플레이어가 두 직선 사이에 있으면
		m_info.y = y - (m_info.cy * 0.5f);  // 플레이어 y = y - (플레이어 사이즈의 반)
}

void Player::Initialize(void)
{
	m_id = OBJ::PLAYER;
	m_dir = DIR::RIGHT;

	m_info.cx = 100.f;
	m_info.cy = 100.f;

	m_speed = 4.f;

	// 점프
	m_time = 0.f;
	m_jump = false;
	m_jump_power = 50.f;
	m_jump_y = 0.f;

	m_dead = false;
	
	// 무적
	is_vaild = true;
	m_vaild_time = GetTickCount();				
	cool_time = 1000.f;

	move_screen = false;
	m_screen_time = GetTickCount();
	move_time = 2000.f;

	m_attack = false;

	// 오프셋
	m_offset_x = WINCX >> 1; // 오프셋x = 클라 가로 사이즈 / 2 
	m_offset_y = WINCY >> 1; // 오프셋y = 클라 세로 사이즈 / 2 

	// 블럭 충돌
	BmpManager::GetInstance()->InsertBmp(L"../Image/Player_L.bmp", L"Player_L");
	BmpManager::GetInstance()->InsertBmp(L"../Image/Player_R.bmp", L"Player_R");

	BmpManager::GetInstance()->InsertBmp(L"../Image/exe.bmp", L"exe");
	BmpManager::GetInstance()->InsertBmp(L"../Image/exe2.bmp", L"exe2");

	// 프레임 
	m_frame_key = L"Player_R";

	m_pre_state = STATE::IDLE;
	m_cur_state = STATE::IDLE;

	m_frame.frame_start = 0;
	m_frame.frame_end = 2;
	m_frame.frame_scene = 2;
	m_frame.frame_speed = 200;
	m_frame.frame_time = GetTickCount();
	
}

int Player::Update(void)
{
	if (true == m_dead)
		return OBJ_DEAD;

	KeyInput();
	Jumping();

	UpdateRect();

	StateChange();
	MoveFrame();


	return OBJ_NOEVENT;
}

void Player::LateUpdate(void)
{
	SetVaild();
	//OffSet();
}

void Player::Render(HDC dc)
{

	int scroll_x = (int)ScrollManager::GetInstance()->GetScrollX();
	int scroll_y = (int)ScrollManager::GetInstance()->GetScrollY();

	HDC	mem_dc = BmpManager::GetInstance()->FindImage(m_frame_key);

	// 확인 용도
	//Rectangle(dc, m_rect.left + scroll_x, m_rect.top + scroll_y, m_rect.right + scroll_x, m_rect.bottom + scroll_y);


		if (is_vaild)
		{
			if ((GetTickCount() / 100) % 2 == 0)
				GdiTransparentBlt(dc,				//	복사 받을, 최종적으로 그림을 그릴 DC
					int(m_rect.left - 50 + scroll_x),	//	2, 3인자 복사 받을 위치의 좌표를 전달
					int(m_rect.top - 50.f + scroll_y),
					(int)m_info.cx * 2,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
					(int)m_info.cy * 2,
					mem_dc,							// 비트맵 정보를 가지고 있는 DC
					m_frame.frame_start * (int)m_info.cx * 2,// 7,8인자 비트맵을 출력할 시작좌표
					m_frame.frame_scene * (int)m_info.cy * 2,
					200,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
					200,
					RGB(255, 255, 255));
		}			// 제거하고자 하는 색상
		else
			GdiTransparentBlt(dc,				//	복사 받을, 최종적으로 그림을 그릴 DC
				int(m_rect.left - 50 + scroll_x),	//	2, 3인자 복사 받을 위치의 좌표를 전달
				int(m_rect.top - 50.f + scroll_y),
				(int)m_info.cx * 2,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
				(int)m_info.cy * 2,
				mem_dc,							// 비트맵 정보를 가지고 있는 DC
				m_frame.frame_start * (int)m_info.cx * 2,// 7,8인자 비트맵을 출력할 시작좌표
				m_frame.frame_scene * (int)m_info.cy * 2,
				200,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
				200,
				RGB(255, 255, 255));

	
}

void Player::Release(void)
{
	
}

void Player::StateChange()
{
	if (m_pre_state != m_cur_state)
	{
		switch (m_cur_state)
		{
		case STATE::IDLE:
			m_frame.frame_start = 0;
			m_frame.frame_end = 2;
			m_frame.frame_scene = 2;
			m_frame.frame_speed = 200;
			m_frame.frame_time = GetTickCount();
			break;

		case STATE::WALK:
			m_frame.frame_start = 0;
			m_frame.frame_end = 5;
			m_frame.frame_scene = 0;
			m_frame.frame_speed = 100;
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
			m_frame.frame_start = 1;
			m_frame.frame_end = 2;
			m_frame.frame_scene = 4;
			m_frame.frame_speed = 150;
			m_frame.frame_time = GetTickCount();
			break;

		case STATE::HIT:
			break;

		case STATE::DEAD:
			break;
		}

		m_pre_state = m_cur_state;
	}
}


void Player::SetVaild()
{
	if (is_vaild && m_vaild_time + cool_time < GetTickCount())
	{
		m_vaild_time = GetTickCount();
		is_vaild = false;
	}
}

void Player::SetCollision(Obj* obj, DIR::DIR _eDIR)
{
	if (m_dead)
		return;

	if (obj->GetID() == BLOCK::DEFAULT)
	{
		switch (_eDIR)
		{
		case DIR::DOWN: 
			if (m_state == STATE::JUMP)
				m_state = STATE::IDLE;
			break;
		case DIR::UP:
			break;
		case DIR::LEFT:
			m_info.x += m_speed;
			//ScrollManager::GetInstance()->SetScrollX(-m_speed);
			break;
		case DIR::RIGHT:
			m_info.x -= m_speed;
			//ScrollManager::GetInstance()->SetScrollX(m_speed);
			break;
		}
	}
	else 
	if (obj->GetID() == OBJ::MONSTER)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
			if (!is_vaild)
			{
				m_jump_y = m_info.y;	// jump_y에 플레이어 y좌표를 대입
				m_jump = true;			// false 에서 true로 변환
				m_time = 0.f;

				is_vaild = true;
				m_vaild_time = GetTickCount();
				cool_time = 50.f;
			}
			// false 에서 true로 변환
			else
			break;
		default:
			if (!is_vaild)//ScrollManager::GetInstance()->SetScrollX(m_speed);
			{
				DataManager::GetInstance()->AddEnergy(-1);
				is_vaild = true;
				m_vaild_time = GetTickCount();
				cool_time = 1500.f;
				break;
			}
			else
			{
				is_vaild = true;
				m_vaild_time = GetTickCount();
				cool_time = 100.f;
			}
		}
	}
	else if (obj->GetID() == ITEM::FOOD)
	{
		switch (_eDIR)
		{
		case DIR::DOWN:
		case DIR::UP:
		case DIR::LEFT:
		case DIR::RIGHT:
			break;
		}	
	}
	else if (obj->GetID() == OBSTACLE::SAVE)
	{
		
		switch (_eDIR)
		{
		case DIR::UP:
		case DIR::LEFT:
		case DIR::RIGHT:
		case DIR::DOWN:
			break;
		}
	}
}