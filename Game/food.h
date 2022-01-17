#pragma once
#ifndef FOOD_H_
#define FOOD_H_

#include "item.h"

class Food : public Item
{

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);


	virtual void		SetCollision(Obj* obj, DIR::DIR _dir)override;
};

#endif // !FOOD_H_
