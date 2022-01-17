#pragma once
#include "scene.h"
class Clear :
	public Scene
{
private:
	HWND		m_video;

public:
	Clear();
	virtual ~Clear();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

