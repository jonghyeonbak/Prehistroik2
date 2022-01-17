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
	m_dc = GetDC(g_hWnd);   // g_hwnd 핸들을 얻어와 m_dc에 복사

	// 백버퍼와 백은 더블 버퍼링을 위해 필요하다.
	// 이미지 두 장을 번갈아가며 꺼내, 화면에 점멸부분이 잘 보이지 않게 해준다.
	
	
	BmpManager::GetInstance()->InsertBmp(L"../Image/BackBuffer2.bmp", L"BackBuffer");
	BmpManager::GetInstance()->InsertBmp(L"../Image/Back.bmp", L"Back");

	SoundManager::Get_Instance()->Initialize();
	// 시작 하자마자 로고를 띄워주는 코드
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
	// 지금 화면이 로고라면 리턴
	if (SCENE_LOGO == SceneManager::GetInstance()->GetScene())
		return;

	HDC	hMemDC = BmpManager::GetInstance()->FindImage(L"BackBuffer");

	HDC	hBackBufferDC = BmpManager::GetInstance()->FindImage(L"Back");
	BitBlt(hBackBufferDC,	//	복사 받을, 최종적으로 그림을 그릴 DC
		0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		WINCX,				//4,5인자 복사 받을 X,Y의 길이를 전달
		WINCY,
		hMemDC,				// 비트맵 정보를 가지고 있는 DC
		0,					// 7,8인자 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);

	// 백 버퍼를 가져와 그린다.
	SceneManager::GetInstance()->Render(hBackBufferDC);

	BitBlt(m_dc,			//	복사 받을, 최종적으로 그림을 그릴 DC
		0,					// 2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		WINCX,				//4,5인자 복사 받을 X,Y의 길이를 전달
		WINCY,
		hBackBufferDC,		// 비트맵 정보를 가지고 있는 DC
		0,					// 7,8인자 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);


}

void MainGame::Release(void)
{
	// 사용한 dc 지우기
	ReleaseDC(g_hWnd, m_dc);


	// 순서 중요!!
	SoundManager::Get_Instance()->Destroy_Instance();
	SceneManager::GetInstance()->DestroyIntance();
	ScrollManager::GetInstance()->DestroyIntance();
	BmpManager::GetInstance()->DestroyIntance();
	KeyManager::GetInstance()->DestroyInstance();
	//LineManager::GetInstance()->DestroyInstance(); // 라인 매니저 인스턴스 삭제
	//ObjManager::GetInstance()->DestroyInstance();
}