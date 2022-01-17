#pragma once

#include "Stage.h"

class Stage2 : public Stage
{
private:
	bool	in_the_cave;

public:
	Stage2();
	~Stage2();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;

	void MapScroll();
};

