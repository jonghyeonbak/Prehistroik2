#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include "obj.h"
#include "include.h"

class Bullet	: public Obj
{
private:
	int			m_anim_num = 0;
	DWORD		m_anim_time;
	STATE::ID	m_pre_state;
	STATE::ID	m_cur_state;

	DWORD			m_AnimTime;


private:
	int m_AnimNum = 0;

public:
	void			SetParentID(OBJ::ID _id) { parent_id = _id; }
	const OBJ::ID& GetParentID() const { return parent_id; }
	void	SetCollision(Obj* obj, DIR::DIR _eDIR);

protected:
	OBJ::ID		parent_id;

public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void)override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;

};

#endif // !BULLET_H_
