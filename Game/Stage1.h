#pragma once
#ifndef STAGE1_H_
#define STAGE1_H_

#include "stage.h"

class Stage1 : public Stage
{
private:
	bool	in_the_cave;

public:
	Stage1();
	virtual ~Stage1();


public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;

	
	void MapScroll();

};

#endif // !STAGE_H_
