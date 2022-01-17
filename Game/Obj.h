#pragma once
#ifndef OBJ_H_
#define OBJ_H_

#include "include.h"

class Obj
{
protected:
	RECT		m_rect;
	INFO		m_info;
	bool		m_dead;
	float		m_speed;
	int			m_draw_id;
	TCHAR*	    m_frame_key;
	FRAME		m_frame;
	DIR::DIR	m_dir;
	OBJ::ID		m_id;
	STATE::ID	m_state = STATE::IDLE;

	bool		is_vaild;
	DWORD		m_vaild_time;
	float		cool_time;

	bool		m_distance = false;
	DWORD		m_distime = GetTickCount();

public:
	Obj();
	virtual ~Obj();

	bool			GetDead() { return m_dead; }
	const INFO&		GetInfo(void) const { return m_info; }
	const RECT&		GetRect(void) const { return m_rect; }
	const int &		GetDrawID(void) const { return m_draw_id; }
	OBJ::ID			GetID() { return m_id; }
	float			GetYSize() { return m_info.cy; }
	const STATE::ID GetState(void) const { return m_state; }
	float			GetSpeed() { return m_speed; }
	bool			GetVaild() { return is_vaild; }

public:
	void			SetPos(float x_, float y_);
	void			SetPosX(float _x);
	void			SetPosY(float _y);
	void			SetState(STATE::ID _state) { m_state = _state; }
	void			SetDrawID(int drawid);
	void			SetFrameKey(TCHAR* framekey);
	void			SetDirection(DIR::DIR dir);
	void			SetDead(bool _bool) { m_dead = _bool; }
	virtual void	SetCollision(Obj* obj, DIR::DIR _eDIR) {}; // (CObj* pObj)
public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	LateUpdate(void)PURE;
	virtual void	Render(HDC dc)PURE;
	virtual void	Release(void)PURE;

	void			UpdateRect(void);
	void			MoveFrame(void);
};

#endif // !OBJ_H_
