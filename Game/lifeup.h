#pragma once
#include "item.h"
class Lifeup :
	public Item
{
public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);


	virtual void		SetCollision(Obj* obj, DIR::DIR _dir)override;
};

