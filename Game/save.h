#pragma once

#include "Obj.h"
class Save : public Obj
{
protected:
	OBSTACLE::ID		m_block_id;
	bool				m_is_invisible;
	HDC					mem_dc;
	bool				m_crush;
public:
	Save();
	virtual ~Save();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	virtual void Render(HDC dc) override;
	virtual void Release(void) override {};

	virtual void SetCollision(Obj* obj, DIR::DIR _eDIR) override;

public:
	virtual void	Setup(OBSTACLE::ID _type, bool _isInvisible = false);
	virtual void	StartAnimation() {};
	virtual void	UpdateAnimation() {};
	virtual void	DestoryBlock() {};

public:
	const OBSTACLE::ID& Get_BlockId() const { return m_block_id; };

};



