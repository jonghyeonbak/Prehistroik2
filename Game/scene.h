#pragma once
#ifndef  SCENE_H_
#define  SCENE_H_

#include "include.h"

class Scene abstract //추상화, scene을 관리하기 클래스들을 모으기 위해 만들어준 클래스
{
protected:
	GAME::ID		m_game_num;
	SCENEID			m_scene_num;

public:
	Scene();
	virtual ~Scene();

public:
	virtual void	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	LateUpdate(void)PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release(void)PURE;

public:
	GAME::ID		GetGameNum() { return m_game_num; }
	void			SetGameNum(GAME::ID i) { m_game_num = i; }

	SCENEID			GetGameNum1() { return m_scene_num; }
	void			SetGameNum1(SCENEID i) { m_scene_num = i; }

};

#endif // ! SCENCE_H_