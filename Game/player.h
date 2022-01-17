#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include "obj.h"
#include "include.h"

class Player : public Obj
{
private:
	POINT		m_gun;
	bool		m_walk;
	bool		m_jump;
	float		m_jump_y;
	float		m_jump_power;
	float		m_time;
	int			m_offset_x;			// 플레이어가 좌우로 움직이면 x좌표만 알면 된다.
	int			m_offset_y;
	STATE::ID	m_pre_state;
	STATE::ID	m_cur_state;
	float		g_fSound = 0; 

	// 방해물 충돌

	// 무적
	/*bool		is_vaild;
	DWORD		m_vaild_time;
	float		cool_time;*/

	//화면 이동
	bool		move_screen;
	DWORD		m_screen_time;
	float		move_time;

private:
	bool					m_attack;
	DWORD					m_attack_time = 0;

public:
	Player();
	virtual ~Player();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;

	virtual	void SetCollision(Obj* obj, DIR::DIR _eDIR) override;

	
	void		SetJump(bool bool_) { m_jump = bool_; }
	void		SetY(float y_) { m_info.y = y_; };

	// 무적
	void		SetVaild();
	//void		OffSet(void);		// 플레이어가 이동하는 만큼 다른 물체도 이동하는 함수 

	// 방해물


private:
	void		KeyInput(void);
	void		Jumping(void);
	void		StateChange(void);  // 화면 전환

};

#endif // !PLAYER_H_
