#include "stdafx.h"
#include "my_button.h"
#include "bmp_manager.h"
#include "key_manager.h"
#include "scene_manager.h"

MyButton::MyButton()
{
}


MyButton::~MyButton()
{
	Release();
}

void MyButton::Initialize(void)
{
	m_info.cx = 150.f;
	m_info.cy = 150.f;
}

int MyButton::Update(void)
{
	UpdateRect();

	return OBJ_NOEVENT;
}

void MyButton::LateUpdate(void)
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_rect, pt))
	{
		if (KeyManager::GetInstance()->KeyDown(VK_LBUTTON))						// 왼쪽 마우스 누르면
		{
			if (!lstrcmp(L"Button_Start", m_frame_key))							// 스타트 버튼을 누르면
			{
				SceneManager::GetInstance()->SceneChange(SCENE_STAGE);			// stage로 이동
			}


			return;
		}
		m_draw_id = 1;
	}

	else
		m_draw_id = 0;
}

void MyButton::Render(HDC dc)
{
	HDC	hMemDC = BmpManager::GetInstance()->FindImage(m_frame_key);

	GdiTransparentBlt(dc,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_rect.left),				//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_rect.top),
		(int)m_info.cx,					//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_info.cy,	
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		m_draw_id * (int)m_info.cx,		// 7,8인자 비트맵을 출력할 시작좌표
		0,
		(int)m_info.cx,					// 9, 10인자 비트맵의 X,Y의 길이를 전달
		(int)m_info.cy,
		RGB(255, 255, 255));
}

void MyButton::Release(void)
{

}
