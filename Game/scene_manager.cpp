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
	if (nullptr != m_scene)		// �� �����?
		SafeDelete(m_scene);

	m_scene_id = scene;			// ������ ��� ������, �޴��� �Ѿ�� ����
								// �̰� �����ָ� �Ͼ� ȭ�鿡�� ����� ����.
								// 30�� �ҿ�

	switch (scene)
	{
	case SCENE_LOGO:
		m_scene = new Logo;			// �ΰ� ����
		break;

	case SCENE_STAGE1:
		m_scene = new Stage1;		// �������� ����
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

	m_scene->Initialize();			// �ش� ���� �̴ϼȶ����� 
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