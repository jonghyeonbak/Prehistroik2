#pragma once
#ifndef STAGE_H_
#define STAGE_H_

#include "scene.h"

class Stage : public Scene
{
protected:

	GAME::RESULT m_result;
	float		sound = 0;

	HDC			drawing_dc = NULL;
	bool		is_clear;
	bool		is_fail;
	HWND		m_video;

	list<POINT> save_point;
	POINT		end_line;

	bool		create;
	DWORD		create_time = 0;

	HFONT		hFont = NULL, oldFont = NULL; // 폰트 설정

	

public:
	Stage();
	virtual ~Stage();

public:
	void		KeyInput();
	void		InitUi();
	void		RenderData(HDC _hdc);

public:
	void	FallDown();

	void	SetResult(GAME::RESULT result) { m_result = result; };
	void	Result(HDC dc);
	void	CheckState();
	void	ShowWinLose(HDC _hdc);

public:
	void	SetPlayerToSavePoint();
	void	UpdateSavePoint();
	void	CheckEndLine();

public:
	virtual void Initialize(void) override;
	virtual int  Update(void) override;
	virtual void LateUpdate(void) override;
	virtual void Release(void) override;
	
	

};

#endif // !STAGE_H_
