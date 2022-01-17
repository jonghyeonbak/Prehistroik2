#pragma once
#ifndef LOGO_H_
#define LOGO_H_

#include "scene.h"

class Logo : public Scene		// �ΰ� ����ϴ� Ŭ����
{
private:                            
	HWND		m_video;

public:
	Logo();
	~Logo();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Render(HDC dc) override;
	virtual void Release(void) override;
};

#endif // !LOGO_H_
