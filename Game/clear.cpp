#include "stdafx.h"
#include "clear.h"

#include "bmp_manager.h"
#include "key_manager.h"
#include "scene_manager.h"

Clear::Clear()
{
}


Clear::~Clear()
{
	Release();
}


void Clear::Initialize(void)
{
	// �̹��� ���Ͽ��� �ΰ� ���� �����ϱ�
	//BmpManager::GetInstance()->InsertBmp(L"../Image/Logo/Logo.bmp", L"Logo");

	// ������ ���� ã���� �̰ɷ�
	m_video = MCIWndCreate(g_hWnd,		// �θ��� ������ �ڵ��� ����
		nullptr,	// mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// �������� ��� ����
		L"../Video/Loading.wmv"); // ����� ������ ���

	MoveWindow(m_video, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_video);	// �������� ���
}

int Clear::Update(void)
{
	return 0;
}

void Clear::LateUpdate(void)
{
	if (MCIWndGetLength(m_video) <= MCIWndGetPosition(m_video)
		|| KeyManager::GetInstance()->KeyDown(VK_RETURN))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE2);
		return;
	}
}

void Clear::Render(HDC dc)
{
	// Ű������ ���� ã�ƿ���
	//HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Logo");

	//// �̹����� ȭ�鿡 ������ִ� �Լ�
	//BitBlt(dc, 0, 0, WINCX, WINCY, mem_dc, 0, 0, SRCCOPY);

}

void Clear::Release(void)
{
	MCIWndClose(m_video);
}
