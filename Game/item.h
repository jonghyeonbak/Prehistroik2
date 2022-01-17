#pragma once
#ifndef ITEM_H_
#define	ITEM_H_

#include "Obj.h"

class Item : public Obj
{
protected:
	float				m_Force = 0.f; // �Ʒ��� ���ϴ� ��
	float				m_fGravity = 0.5f; // �߷��� ��ΰ� ������ �־���ϴ°� static ����� ������
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
