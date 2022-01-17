#pragma once
#ifndef LOSE_H_
#define LOSE_H_

#include "scene.h"

class Lose : public Scene		// 로고를 담당하는 클래스
{
private:
	HWND		m_video;

public:
	Lose();
	~Lose();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

#endif // !LOGO_H_