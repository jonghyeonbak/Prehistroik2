#include "stdafx.h"
#include "my_menu.h"
#include "bmp_manager.h"
#include "abstractfactory.h"
#include "my_button.h"
#include "obj_manager.h"

MyMenu::MyMenu()
{
}


MyMenu::~MyMenu()
{
	Release();
}

void MyMenu::Initialize(void)
{
	BmpManager::GetInstance()->InsertBmp(L"../Image/Button/Start.bmp", L"Button_Start");

	BmpManager::GetInstance()->InsertBmp(L"../Image/Menu/Menu.bmp", L"Menu"); 

	Obj*		obj = AbstractFactory<MyButton>::Create(200.f, 500.f);
	dynamic_cast<MyButton*>(obj)->SetFrameKey(L"Button_Start");
	ObjManager::GetInstance()->AddObject(OBJID::UI, obj);
}

int MyMenu::Update(void)
{
	ObjManager::GetInstance()->Update();

	return 0;
}

void MyMenu::LateUpdate(void)
{
	ObjManager::GetInstance()->LateUpdate();
}

void MyMenu::Render(HDC dc)
{
	HDC	mem_dc = BmpManager::GetInstance()->FindImage(L"Menu");

	BitBlt(dc, 0, 0, WINCX, WINCY, mem_dc, 0, 0, SRCCOPY);

	ObjManager::GetInstance()->Render(dc);
}

void MyMenu::Release(void)
{
	ObjManager::GetInstance()->DeleteID(OBJID::UI);
}
