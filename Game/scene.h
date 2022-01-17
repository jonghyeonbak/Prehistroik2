#pragma once
#ifndef  SCENE_H_
#define  SCENE_H_

#include "include.h"

class Scene abstract //�߻�ȭ, scene�� �����ϱ� Ŭ�������� ������ ���� ������� Ŭ����
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