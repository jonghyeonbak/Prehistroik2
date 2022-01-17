#include "stdafx.h"
#include "stage2.h"
#include "manager.h"
#include "abstractfactory.h"
#include "player.h"

Stage2::Stage2()
{
}


Stage2::~Stage2()
{
	Release();
}

void Stage2::Initialize(void)
{
	Stage::Initialize();

	in_the_cave = false;
	is_clear = false;
	is_fail = false;
	SetGameNum(GAME::STAGETWO);
	m_result = GAME::NONE;


	LineManager::GetInstance()->LoadData(STAGE2_LINE);
	LineManager::GetInstance()->Initialize();

	SoundManager::Get_Instance()->PlayBGM(L"stage2.wav", 7);


	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GRAPE, 350.f, 1300.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::LIFEUP, 750, 1300.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DOUGHNUT, 1400.f, 1100.f);

	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DEATH, 5620.f, 1360.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DEATH, 5640.f, 1350.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 5850.f, 1350.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 5900.f, 1350.f);

	//동굴 1 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::SCORE750, 250.f, 1920.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::EGG, 300.f, 1900.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 350.f, 1900.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::EXE, 550.f, 1890.f);


	//동굴2 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::SCORE20000, 1000.f, 1900.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::SCORE20000, 1100.f, 1900.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GOLD, 1400.f, 1950.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GOLD, 1440.f, 1950.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GOLD, 1420.f, 1900.f);

	//동굴3 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDLE, 1850.f, 1880);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CHOCO, 2000.f, 1850);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::BEER, 2050.f, 1820.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CAKE, 2100.f, 1850.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DOUGHNUT, 2150.f, 1880.f);

	ScrollManager::GetInstance()->SetScrollY(110.f);
	ScrollManager::GetInstance()->InitScrollX(0.f);

	// 스크롤 위치에 따른 플레이어 좌표 수정
	ObjManager::GetInstance()->AddObject(OBJ::PLAYER, AbstractFactory<Player>::Create(ScrollManager::GetInstance()->GetScrollX() + 100.f, ScrollManager::GetInstance()->GetScrollY() + 2070));

	DataManager::GetInstance()->Initialize();

	InitUi();

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::SNAKE, 500.f, 1070.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::SNAKE, 1500.f, 1070.f, DIR::LEFT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::SPIDER, 900.f, 1750.f, DIR::DOWN);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::SPIDER, 1200.f, 1750.f, DIR::DOWN);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BEE, 400.f, 1100.f, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BEE, 500.f, 1150.f, DIR::RIGHT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::OLD_BIRD, 4200.f, 1330.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::OLD_BIRD, 4500.f, 1350.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::OLD_BIRD, 5200.f, 1300.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::OLD_BIRD, 5800.f, 1325.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::OLD_BIRD, 6000.f, 1350.f, DIR::LEFT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::DINO, 7600, 1350.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BIRD, 9700, 1300.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BIRD, 10500, 1280.f, DIR::LEFT);


	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::DOG, 7200, 1350.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::DOG, 7300.f, 1350.f, DIR::LEFT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::DINO, 7900.f, 1350.f, DIR::LEFT);
	
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::HUMAN, 1100.f, 1100.f, DIR::RIGHT);


	//	BmpManager::GetInstance()->InsertBmp(STAGE1_BMP, STAGE1_KEY);
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage2_1.bmp", L"stage2_1");
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage2_2.bmp", L"stage2_2");
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage2_3.bmp", L"stage2_3");
	BmpManager::GetInstance()->InsertBmp(L"../Image/stage2_4.bmp", L"stage2_4");


}

int Stage2::Update(void)
{
	KeyInput();
	MapScroll();
	//OffSet();

	LineManager::GetInstance()->Update();
	ObjManager::GetInstance()->Update();


	return 0;
}


void Stage2::LateUpdate(void)
{
	LineManager::GetInstance()->LateUpdate();
	ObjManager::GetInstance()->LateUpdate();
	DataManager::GetInstance()->LateUpdate();

	UpdateSavePoint();

	if (ObjManager::GetInstance()->GetPlayerInfo().x >= 7580.f &&
		ObjManager::GetInstance()->GetPlayerInfo().y >= 1300.f)
	{
		SoundManager::Get_Instance()->StopAll();
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE3);
	}
	//CheckEndLine();
	CheckState();
}

void Stage2::Render(HDC dc)
{
	float x = ScrollManager::GetInstance()->GetScrollX();
	float y = ScrollManager::GetInstance()->GetScrollY();


	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage2_1");
	GdiTransparentBlt(dc, (int)x, (int)y  + 830, 2000, 1200, drawing_dc, 0, 0, 1000, 600, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage2_2");
	GdiTransparentBlt(dc, (int)x + 2000, (int)y + 830, 2000, 1200, drawing_dc, 0, 0, 1000, 600, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage2_3");
	GdiTransparentBlt(dc, (int)x + 4000, (int)y + 830, 2000, 1200, drawing_dc, 0, 0, 1000, 600, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"stage2_4");
	GdiTransparentBlt(dc, (int)x + 6000, (int)y + 830, 1668, 1200, drawing_dc, 0, 0, 834, 600, RGB(255, 255, 255));


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

void Stage2::Release(void)
{


	ScrollManager::GetInstance()->Release();
	LineManager::GetInstance()->Release();
	ObjManager::GetInstance()->Release();

	save_point.erase(save_point.begin(), save_point.end());
	save_point.clear();
}

void Stage2::MapScroll(void)	// 스테이지1 로 이사		// 플레이어의 이동만큼 다른 물체도 이동시키는 함수
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

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 3050 &&
			-2950 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-2951 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-2950);
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

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 4250 &&
			-4150 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-4151 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-4150);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 4850 &&
			-4750 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-4751 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-4750);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 5450 &&
			-5350 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-5351 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-5350);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 6050 &&
			-5950 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-5951 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-5950);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 6650 &&
			-6550 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-6551 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-6550);
		}

		if (ObjManager::GetInstance()->GetPlayerInfo().x > 7250 &&
			-6845 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-6846 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-6845);
		}

	}

	// 캐릭터 이동 먼저 -> 스크롤 동굴로 이동 
	// 1번 동굴 들어가기 4000 4200
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 650&&
		ObjManager::GetInstance()->GetPlayerInfo().x < 1250 &&
		in_the_cave == false)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(100.f);
			ScrollManager::GetInstance()->SetScrollY2(-1500.f);

			ObjManager::GetInstance()->SetPlayerPos(20, 1930.f);

			in_the_cave = true;

		}
	}

	// 1번 동굴 나오기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 10 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 100 &&
		in_the_cave == true)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-800.f);
			ScrollManager::GetInstance()->SetScrollY2(-940.f);

			ObjManager::GetInstance()->SetPlayerPos(940, 1070.f);

			in_the_cave = false;

		}
	}

	// 2번 동굴 들어가기 4250
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 4250 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 4500 &&
		in_the_cave == false)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-750.f);
			ScrollManager::GetInstance()->SetScrollY2(-1500.f);

			ObjManager::GetInstance()->SetPlayerPos(900, 1930.f);

			in_the_cave = true;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}

	// 2번 동굴 나오기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 1400 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 1450 &&
		in_the_cave == true)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-4200.f);
			ScrollManager::GetInstance()->SetScrollY2(-940.f);

			ObjManager::GetInstance()->SetPlayerPos(4330, 1070.f);

			in_the_cave = false;
		}
	}

	// 3번 동굴 들어가기 6350
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 6350 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 6650 &&
		in_the_cave == false)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-1550.f);
			ScrollManager::GetInstance()->SetScrollY2(-1500.f);

			ObjManager::GetInstance()->SetPlayerPos(1660, 1930.f);

			in_the_cave = true;
		}
	}

	// 3번 동굴 나오기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 2150 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 2250 &&
		in_the_cave == true)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-6400.f);
			ScrollManager::GetInstance()->SetScrollY2(-940.f);

			ObjManager::GetInstance()->SetPlayerPos(6500, 1070.f);

			in_the_cave = false;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}
	// 올라타고 내려가기 만들기

	// 상하 스크롤

}