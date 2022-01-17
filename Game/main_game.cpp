#include "stdafx.h"
#include "main_game.h"
#include "abstractfactory.h"
#include "manager.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	Release();
}

void MainGame::Initailize(void)
{
	m_dc = GetDC(g_hWnd);   // g_hwnd �ڵ��� ���� m_dc�� ����

	// ����ۿ� ���� ���� ���۸��� ���� �ʿ��ϴ�.
	// �̹��� �� ���� �����ư��� ����, ȭ�鿡 ����κ��� �� ������ �ʰ� ���ش�.
	
	
	BmpManager::GetInstance()->InsertBmp(L"../Image/BackBuffer2.bmp", L"BackBuffer");
	BmpManager::GetInstance()->InsertBmp(L"../Image/Back.bmp", L"Back");

	SoundManager::Get_Instance()->Initialize();
	// ���� ���ڸ��� �ΰ� ����ִ� �ڵ�
	SceneManager::GetInstance()->SceneChange(SCENE_LOGO);

}

void MainGame::Update(void)
{
	SceneManager::GetInstance()->Update();
}

void MainGame::LateUpdate(void)
{
	SceneManager::GetInstance()->LateUpdate();
	ScrollManager::GetInstance()->ScrollLock();
}

void MainGame::Render(void)
{
	// ���� ȭ���� �ΰ��� ����
	if (SCENE_LOGO == SceneManager::GetInstance()->GetScene())
		return;

	HDC	hMemDC = BmpManager::GetInstance()->FindImage(L"BackBuffer");

	HDC	hBackBufferDC = BmpManager::GetInstance()->FindImage(L"Back");
	BitBlt(hBackBufferDC,	//	���� ����, ���������� �׸��� �׸� DC
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,				//4,5���� ���� ���� X,Y�� ���̸� ����
		WINCY,
		hMemDC,				// ��Ʈ�� ������ ������ �ִ� DC
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);

	// �� ���۸� ������ �׸���.
	SceneManager::GetInstance()->Render(hBackBufferDC);

	BitBlt(m_dc,			//	���� ����, ���������� �׸��� �׸� DC
		0,					// 2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,				//4,5���� ���� ���� X,Y�� ���̸� ����
		WINCY,
		hBackBufferDC,		// ��Ʈ�� ������ ������ �ִ� DC
		0,					// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);


}

void MainGame::Release(void)
{
	// ����� dc �����
	ReleaseDC(g_hWnd, m_dc);


	// ���� �߿�!!
	SoundManager::Get_Instance()->Destroy_Instance();
	SceneManager::GetInstance()->DestroyIntance();
	ScrollManager::GetInstance()->DestroyIntance();
	BmpManager::GetInstance()->DestroyIntance();
	KeyManager::GetInstance()->DestroyInstance();
	//LineManager::GetInstance()->DestroyInstance(); // ���� �Ŵ��� �ν��Ͻ� ����
	//ObjManager::GetInstance()->DestroyInstance();
}