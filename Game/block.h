#pragma once
#ifndef BLOCK_H_
#define BLOCK_H_

#include "Obj.h"

class Block : public Obj								// 뛰어 넘어야 하는 발판
{
protected:
	BLOCK::ID		m_block_id;
	bool			m_is_invisible;
	HDC				mem_dc;

public:
	Block();
	virtual ~Block();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override {};
	virtual void Render(HDC dc) override;
	virtual void Release(void) override {};

	virtual void SetCollision(Obj* obj, DIR::DIR _eDIR) override;

public:
	virtual void	Setup(BLOCK::ID _type, bool _isInvisible = false);
	virtual void	StartAnimation() {};
	virtual void	UpdateAnimation() {};
	virtual void	DestoryBlock() {};

public:
	const BLOCK::ID& Get_BlockId() const { return m_block_id; };

};

#endif // !OBJ_H_
