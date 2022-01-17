#include "stdafx.h"
#include "scene_manager.h"
#include "lose.h"
#include "clear.h"

SceneManager*	SceneManager::m_instance = nullptr;

SceneManager::SceneManager()
	:m_scene(nullptr)
{
}


SceneManager::~SceneManager()
{
	Release();
}


void SceneManager::SceneChange(SCENEID scene)
{
	if (nullptr != m_scene)		// 왜 지울까?
		SafeDelete(m_scene);

	m_scene_id = scene;			// 동영상 띄운 다음에, 메뉴로 넘어가는 과정
								// 이거 안해주면 하얀 화면에서 벗어나질 않음.
								// 30분 소요

	switch (scene)
	{
	case SCENE_LOGO:
		m_scene = new Logo;			// 로고 생성
		break;

	case SCENE_STAGE1:
		m_scene = new Stage1;		// 스테이지 생성
		break;

	case SCENE_STAGE2:
		m_scene = new Stage2;
		break;

	case SCENE_STAGE3:
		m_scene = new Stage3;
		break;

	case SCENE_GAME_OVER:
		m_scene = new Lose;
		break;
	case SCENE_CLEAR:
		m_scene = new Clear;
		break;
	}

	m_scene->Initialize();			// 해당 신의 이니셜라이즈 
}

void SceneManager::Update(void)
{
	if (nullptr != m_scene)
		m_scene->Update();
}

void SceneManager::LateUpdate(void)
{
	if (nullptr != m_scene)
		m_scene->LateUpdate();
}

void SceneManager::Render(HDC dc)
{
	if (nullptr != m_scene)
		m_scene->Render(dc);
}

void SceneManager::Release(void)
{
	SafeDelete(m_scene);
}