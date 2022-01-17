#pragma once
#ifndef FINAL_H_
#define FINAL_H_

#include "Obj.h"

class Final : public Obj
{
protected:
	OBSTACLE::ID		m_obstacle_id;
	bool				m_touch;

public:
	Final();
	virtual ~Final();

public:
	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);



	virtual void		SetCollision(Obj* obj, DIR::DIR _dir)override;
};

#endif