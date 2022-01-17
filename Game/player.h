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
	int			m_offset_x;			// �÷��̾ �¿�� �����̸� x��ǥ�� �˸� �ȴ�.
	int			m_offset_y;
	STATE::ID	m_pre_state;
	STATE::ID	m_cur_state;
	float		g_fSound = 0; 

	// ���ع� �浹

	// ����
	/*bool		is_vaild;
	DWORD		m_vaild_time;
	float		cool_time;*/

	//ȭ�� �̵�
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

	// ����
	void		SetVaild();
	//void		OffSet(void);		// �÷��̾ �̵��ϴ� ��ŭ �ٸ� ��ü�� �̵��ϴ� �Լ� 

	// ���ع�


private:
	void		KeyInput(void);
	void		Jumping(void);
	void		StateChange(void);  // ȭ�� ��ȯ

};

#endif // !PLAYER_H_
