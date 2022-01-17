#include "stdafx.h"
#include "logo.h"

#include "bmp_manager.h"
#include "key_manager.h"
#include "scene_manager.h"

Logo::Logo()
{
}


Logo::~Logo()
{
	Release();
}

void Logo::Initialize(void)
{
	// �̹��� ���Ͽ��� �ΰ� ���� �����ϱ�
	//BmpManager::GetInstance()->InsertBmp(L"../Image/Logo/Logo.bmp", L"Logo");
	
	// ������ ���� ã���� �̰ɷ�
	m_video = MCIWndCreate(g_hWnd,		// �θ��� ������ �ڵ��� ����
	nullptr,	// mci�����츦 ����ϴ� �ν��Ͻ� �ڵ�
	WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// �������� ��� ����
	L"../Video/Opening.wmv"); // ����� ������ ���

	MoveWindow(m_video, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_video);	// �������� ���

}

int Logo::Update(void)
{
	return 0;
}

void Logo::LateUpdate(void)
{
	if (MCIWndGetLength(m_video) <= MCIWndGetPosition(m_video)
		|| KeyManager::GetInstance()->KeyDown(VK_RETURN))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE1);
		return;
	}
}

void Logo::Render(HDC dc)
{
	// Ű������ ���� ã�ƿ���
	//HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Logo");

	//// �̹����� ȭ�鿡 ������ִ� �Լ�
	//BitBlt(dc, 0, 0, WINCX, WINCY, mem_dc, 0, 0, SRCCOPY);

}

void Logo::Release(void)
{
	MCIWndClose(m_video);
}
