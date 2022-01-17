#pragma once
#include "monster.h"
class Dog :
	public Monster
{
protected:
	bool					m_jump;
	float					m_jump_y;
	float					m_jump_power;
	float					m_time;
	
private:
	bool					m_walk;
	DWORD					m_walktime = 0;

	bool					m_die;
	DWORD					m_die_time = 0;

	bool		is_vaild;
	DWORD		m_vaild_time;
	float		cool_time;


	STATE::ID	m_pre_state;
	STATE::ID	m_cur_state;

public:
	Dog();
	virtual ~Dog();

public:
	void		Jumping(void);
	void		StateChange();
	void		SetVaild();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;

	virtual void SetCollision(Obj* obj, DIR::DIR _eDIR)override;
};

