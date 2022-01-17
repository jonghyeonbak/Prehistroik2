#include "stdafx.h"
#include "lose.h"

#include "bmp_manager.h"
#include "key_manager.h"
#include "scene_manager.h"

Lose::Lose()
{
}


Lose::~Lose()
{
	Release();
}


void Lose::Initialize(void)
{
	// 이미지 파일에서 로고 사진 저장하기
	//BmpManager::GetInstance()->InsertBmp(L"../Image/Logo/Logo.bmp", L"Logo");

	// 동영상 파일 찾으면 이걸로
	m_video = MCIWndCreate(g_hWnd,		// 부모의 윈도우 핸들을 전달
	nullptr,	// mci윈도우를 사용하는 인스턴스 핸들
	WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// 윈도우의 모양 설정
	L"../Video/gameover.wmv"); // 재생할 파일의 경로

	MoveWindow(m_video, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_video);	// 동영상을 출력

}

int Lose::Update(void)
{
	return 0;
}

void Lose::LateUpdate(void)
{
	if (MCIWndGetLength(m_video) <= MCIWndGetPosition(m_video)
		|| KeyManager::GetInstance()->KeyDown(VK_RETURN))
	{
		return;
	}
}

void Lose::Render(HDC dc)
{
	// 키값으로 사진 찾아오기
	//HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Logo");

	//// 이미지를 화면에 출력해주는 함수
	//BitBlt(dc, 0, 0, WINCX, WINCY, mem_dc, 0, 0, SRCCOPY);

}

void Lose::Release(void)
{
	MCIWndClose(m_video);
}
