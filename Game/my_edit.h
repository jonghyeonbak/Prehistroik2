#pragma once
#ifndef MY_EDIT_H_
#define MY_EDIT_H_

#include "scene.h"

class MyEdit : public Scene
{
public:
	MyEdit();
	virtual ~MyEdit();

private:
	void		KeyInput(void);

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

#endif // !EDIT_T_
