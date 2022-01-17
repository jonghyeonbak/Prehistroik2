#pragma once
#ifndef MY_MENU_H_
#define MY_MENU_H_

#include "scene.h"

class MyMenu : public Scene
{
public:
	MyMenu();
	virtual ~MyMenu();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

#endif // !MY_MENU_H_