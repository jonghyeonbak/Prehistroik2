#pragma once
#ifndef ITEM_H_
#define	ITEM_H_

#include "Obj.h"

class Item : public Obj
{
protected:
	float				m_Force = 0.f; // 아래로 가하는 힘
	float				m_fGravity = 0.5f; // 중력은 모두가 가지고 있어야하는거 static 만들면 좋을것
	ITEM::ID			m_itemId;
	bool				m_Vaild;
	DWORD				m_VaildTime;

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);

	virtual void		SetCollision(Obj* obj, DIR::DIR _dir, float _fWidth = 0.f, float _fHeight = 0.f);
	const ITEM::ID&		GetItemId()  const { return m_itemId; }
	const bool&			GetVaild() const { return m_Vaild; }

};

#endif // !ITEM
