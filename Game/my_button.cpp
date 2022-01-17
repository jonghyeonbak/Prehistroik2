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
		if (KeyManager::GetInstance()->KeyDown(VK_LBUTTON))						// ���� ���콺 ������
		{
			if (!lstrcmp(L"Button_Start", m_frame_key))							// ��ŸƮ ��ư�� ������
			{
				SceneManager::GetInstance()->SceneChange(SCENE_STAGE);			// stage�� �̵�
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

	GdiTransparentBlt(dc,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_rect.left),				//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_rect.top),
		(int)m_info.cx,					//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_info.cy,	
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		m_draw_id * (int)m_info.cx,		// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		(int)m_info.cx,					// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		(int)m_info.cy,
		RGB(255, 255, 255));
}

void MyButton::Release(void)
{

}
