#include "stdafx.h"
#include "stage3.h"
#include "manager.h"
#include "abstractfactory.h"
#include "player.h"

Stage3::Stage3()
{
}


Stage3::~Stage3()
{
	Release();
}

void Stage3::Initialize(void)
{
	Stage::Initialize();
	in_the_cave = false;
	is_clear = false;
	is_fail = false;
	SetGameNum(GAME::STAGETHREE);
	m_result = GAME::NONE;

	LineManager::GetInstance()->LoadData(STAGE3_LINE);
	LineManager::GetInstance()->Initialize();

	SoundManager::Get_Instance()->PlayBGM(L"stage3.wav", 7);

	ObjPoolManager::GetInstance()->SpawnItem(ITEM::BANANA, 290.f, 230.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::EGG, 350.f, 230.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CHERRY, 500.f, 200.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::PAPRIKA, 570.f, 200.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::SCORE20000, 1030.f, 190.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDLE, 1030.f, 230);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDY, 1180, 220.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::ICECREAM, 1220, 260.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::FOOD, 1400, 220.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GRAPE, 1700.f, 270.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDY2, 1750, 300);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDY, 1780.f, 350.f);

	ObjPoolManager::GetInstance()->SpawnItem(ITEM::ICECREAM2, 1900.f, 400.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDY2, 2000.f, 380.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::BEER, 2100.f, 400.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDY2, 2200.f, 380.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::EGG, 2300.f, 400.f);

	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CAKE, 2490.f, 500.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::ICECREAM2, 2520.f, 440.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::ICECREAM, 2570, 400.f);

	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GAMEOVER, 3160.f, 290.f);


	ScrollManager::GetInstance()->InitScrollX(0.f);
	ScrollManager::GetInstance()->SetScrollY(835.f);
	// 스크롤 위치에 따른 플레이어 좌표 수정
	ObjManager::GetInstance()->AddObject(OBJ::PLAYER, AbstractFactory<Player>::Create(ScrollManager::GetInstance()->GetScrollX() + 450.f, ScrollManager::GetInstance()->GetScrollY() + 400, DIR::LEFT));

	DataManager::GetInstance()->Initialize();
	DataManager::GetInstance()->GetLife();
	DataManager::GetInstance()->GetEnergy();
	DataManager::GetInstance()->GetScore();

	InitUi();

	//ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::MONSTER, 100.f, 400.f);

	//	BmpManager::GetInstance()->InsertBmp(STAGE1_BMP, STAGE1_KEY);
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage3_1.bmp", L"stage3_1");
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage3_2.bmp", L"stage3_2");


}

int Stage3::Update(void)
{
	KeyInput();
	MapScroll();
	//OffSet();

	LineManager::GetInstance()->Update();
	ObjManager::GetInstance()->Update();


	return 0;
}


void Stage3::LateUpdate(void)
{
	LineManager::GetInstance()->LateUpdate();
	ObjManager::GetInstance()->LateUpdate();
	DataManager::GetInstance()->LateUpdate();

	UpdateSavePoint();

	//CheckEndLine();
	CheckState();
}

void Stage3::Render(HDC dc)
{
	float x = ScrollManager::GetInstance()->GetScrollX();
	float y = ScrollManager::GetInstance()->GetScrollY();


	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage3_1");
	GdiTransparentBlt(dc, (int)x, (int)y , 2000, 720, drawing_dc, 0, 0, 1000, 360, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage3_2");
	GdiTransparentBlt(dc, (int)x + 2000, (int)y, 2000, 720, drawing_dc, 0, 0, 1000, 360, RGB(255, 255, 255));


	if (m_result == GAME::NONE)
	{

		// 앞에는 그릴 곳, 오른쪽은 원하는 이미지 사이즈
		//GdiTransparentBlt(dc, (int)x, 0, 4096, 600, drawing_dc, 0, 0, 4096, 600, RGB(255, 255, 255));
		//BitBlt(dc, 0 + x , 0, WINCX, WINCY, drawing_dc, 0, 0, SRCCOPY);

		//LineManager::GetInstance()->Render(dc);
		ObjManager::GetInstance()->Render(dc);

		RenderData(dc);
	}
	else
		Result(dc);


}

void Stage3::Release(void)
{
	ScrollManager::GetInstance()->Release();
	LineManager::GetInstance()->Release();
	ObjManager::GetInstance()->Release();
	BmpManager::GetInstance()->Release();

	save_point.erase(save_point.begin(), save_point.end());
	save_point.clear();
}

void Stage3::MapScroll(void)	// 스테이지1 로 이사		// 플레이어의 이동만큼 다른 물체도 이동시키는 함수
{

	if (ObjManager::GetInstance()->GetPlayerInfo().x <= 8500)
	{
		if (ObjManager::GetInstance()->GetPlayerInfo().x > 660 &&
			-550 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-551 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-550);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 1250 &&
			-1150 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-1151 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-1150);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 1850 &&
			-1750 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-1751 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-1750);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 2450 &&
			-2350 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-2351 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-2350);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 2850 &&
			-2750 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-2751 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-2750);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 3650 &&
			-3550 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-3551 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-3550);
		}
	}
	

	if (ObjManager::GetInstance()->GetPlayerInfo().x < 2000 && ObjManager::GetInstance()->GetPlayerInfo().y  < 370 && ScrollManager::GetInstance()->GetScrollY() > -100)
		ScrollManager::GetInstance()->SetScrollY2(0);

	else if (ObjManager::GetInstance()->GetPlayerInfo().x > 2000  && ScrollManager::GetInstance()->GetScrollY() == 0)
	{
		ScrollManager::GetInstance()->SetScrollY2(-100.f);
	}
	else if (ObjManager::GetInstance()->GetPlayerInfo().x > 2700 && ScrollManager::GetInstance()->GetScrollY() == -100)
	{
		ScrollManager::GetInstance()->SetScrollY2(-190.f);
	}
}