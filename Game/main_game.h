#pragma once
#ifndef MAINGAME_H_
#define MAINGAME_H_	

#include "player.h"
#include "include.h"

#include "key_manager.h"
#include "line_manager.h"
#include "scene_manager.h"

class MainGame
{
private:
	HDC		m_dc;			// 그리기 위한 용도의 변수

public:
	MainGame();
	~MainGame();

public:
	void	Initailize(void);
	void	Update(void);
	void	LateUpdate(void);
	void	Render(void);
	void	Release(void);
};

#endif // !MAINGAME_H_

