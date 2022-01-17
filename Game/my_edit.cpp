#include "stdafx.h"
#include "my_edit.h"
#include "key_manager.h"
#include "scroll_manager.h"
#include "bmp_manager.h"
//#include "tile_manager.h"

MyEdit::MyEdit()
{
}


MyEdit::~MyEdit()
{
}

void MyEdit::KeyInput(void)
{
	if (KeyManager::GetInstance()->KeyPressing(VK_LEFT))
		ScrollManager::GetInstance()->SetScrollX(5.f);

	if (KeyManager::GetInstance()->KeyPressing(VK_RIGHT))
		ScrollManager::GetInstance()->SetScrollX(-5.f);

	if (KeyManager::GetInstance()->KeyPressing(VK_UP))
		ScrollManager::GetInstance()->SetScrollY(5.f);

	if (KeyManager::GetInstance()->KeyPressing(VK_DOWN))
		ScrollManager::GetInstance()->SetScrollY(-5.f);

	if (KeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x -= (long)ScrollManager::GetInstance()->GetScrollX();
		pt.y -= (long)ScrollManager::GetInstance()->GetScrollY();

		//TileManager::GetInstance()->PickingTile(pt, 1, 0);
	}

	//if (KeyManager::GetInstance()->KeyDown(VK_F1))
	//	TileManager::GetInstance()->SaveTile();

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	CTileMgr::Get_Instance()->Load_Tile();*/

}

void MyEdit::Initialize(void)
{
	//TileManager::GetInstance()->Initialize();
}

int MyEdit::Update(void)
{
	KeyInput();
	//TileManager::GetInstance()->Update();

	return 0;
}

void MyEdit::LateUpdate(void)
{
	//TileManager::GetInstance()->LateUpdate();
}

void MyEdit::Render(HDC hDC)
{
	//TileManager::GetInstance()->Render(hDC);
}

void MyEdit::Release(void)
{
	//TileManager::GetInstance()->DestroyIntance();
}
