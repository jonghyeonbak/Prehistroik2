#pragma once
#include "Obj.h"
class Score :
	public Obj
{
public:
	Score();
	virtual ~Score();

	DATA::ID			m_data_id;

	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);
};

