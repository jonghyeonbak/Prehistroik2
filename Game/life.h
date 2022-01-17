#pragma once
#include "Obj.h"
class Life :
	public Obj
{
public:
	Life();
	virtual ~Life();

	DATA::ID			m_data_id;

	virtual void		Initialize(void);
	virtual int			Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC dc);
	virtual void		Release(void);
};

