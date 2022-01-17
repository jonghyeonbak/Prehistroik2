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
	// �̹��� ���Ͽ��� �ΰ� ���� �����ϱ�
	//BmpManager::GetInstance()->InsertBmp(L"../Image/Logo/Logo.bmp", L"Logo");

	// ������ ���� ã���� �̰ɷ�
	m_video = MCIWndCreate(g_hWnd,		// �θ��� ������ �ڵ��� ����
	nullptr,	// mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�
	WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// �������� ��� ����
	L"../Video/gameover.wmv"); // ����� ������ ���

	MoveWindow(m_video, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_video);	// �������� ���

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
	// Ű������ ���� ã�ƿ���
	//HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Logo");

	//// �̹����� ȭ�鿡 ������ִ� �Լ�
	//BitBlt(dc, 0, 0, WINCX, WINCY, mem_dc, 0, 0, SRCCOPY);

}

void Lose::Release(void)
{
	MCIWndClose(m_video);
}
