#pragma once
#ifndef MY_BUTTON_H_
#define MY_BUTTON_H_

#include "obj.h"

class MyButton : public Obj
{
public:
	MyButton();
	virtual ~MyButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

#endif // !MY_BUTTON_H_
