#pragma once
#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "scene.h"

#include "logo.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"

class SceneManager
{
private:
	static SceneManager* m_instance;
	Scene*				 m_scene;
	SCENEID				 m_scene_id;

public:
	SceneManager();
	~SceneManager();

public:
	SCENEID		GetScene(void) { return m_scene_id; }

public:
	void		SceneChange(SCENEID scene);	//화면 전환 함수
	void		Update(void);
	void		LateUpdate(void);
	void		Render(HDC dc);
	void		Release(void);

public:
	static	SceneManager*		GetInstance(void)
	{
		if (nullptr == m_instance)
			m_instance = new SceneManager;

		return m_instance;
	}

	static	void		DestroyIntance(void)
	{
		if (nullptr != m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};

#endif // !SCENE_MANAGER_H_
