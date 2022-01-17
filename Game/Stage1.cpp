#include "stdafx.h"
#include "stage1.h"
#include "abstractfactory.h"
#include "player.h"
#include "manager.h"
#include "monster.h"
#include "block.h"
#include "food.h"

Stage1::Stage1()
{
}


Stage1::~Stage1()
{
	Release();
}

void Stage1::Initialize(void)
{
	Stage::Initialize();

	in_the_cave = false;
	is_clear = false;
	is_fail = false;
	SetGameNum(GAME::STAGEONE);
	m_result = GAME::NONE;

	create = false;
	create_time = GetTickCount();


	LineManager::GetInstance()->LoadData(STAGE1_LINE);
	LineManager::GetInstance()->Initialize();


	ObjPoolManager::GetInstance()->SpawnObstacle(BLOCK::DEFAULT, 1200.f, 1350.f);
	ObjPoolManager::GetInstance()->SpawnObstacle(BLOCK::DEFAULT, 7200, 1150.f);

	ObjPoolManager::GetInstance()->SpawnObstacle2(OBSTACLE::SAVE, 4250, 1470.f);
	ObjPoolManager::GetInstance()->SpawnObstacle2(OBSTACLE::SAVE, 6220, 1140.f);

	// 동굴 1 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DEATH, 1110.f, 153.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDLE2, 1240.f, 270);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CANDLE, 1360.f, 270);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GOLD, 1300.f, 270);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CHOCO, 1400.f, 270);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::LIFEUP, 1045.f, 125.f);
	
	// 동굴 2 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::FOOD, 3530.f, 150.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::GRAPE, 3400.f, 280.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DOUGHNUT, 3430.f, 220.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CAKE, 3600.f, 170.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CHERRY, 3650.f, 220.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::BANANA, 3680.f, 280.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::PAPRIKA, 3800.f, 300.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::BEER, 3470.f, 180.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 3600.f, 300.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 3600.f, 280.f);
	
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 1800.f, 1120.f);


	// 피니시 라인 아래 아이템
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::CHOCO, 7150.f, 1520.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::DOUGHNUT, 7200.f, 1520.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::EGG, 7250.f, 1520.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::PAPRIKA, 7300.f, 1520.f);
	ObjPoolManager::GetInstance()->SpawnItem(ITEM::HEART, 7350.f, 1520.f);


	ScrollManager::GetInstance()->SetScrollY(-968.f);

	// 스크롤 위치에 따른 플레이어 좌표 수정
	ObjManager::GetInstance()->AddObject(OBJ::PLAYER, AbstractFactory<Player>::Create(ScrollManager::GetInstance()->GetScrollX()+ 200.f, ScrollManager::GetInstance()->GetScrollY() + 1070));

	DataManager::GetInstance()->Initialize();

	InitUi();


	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::MONSTER, 1200.f, 400.f, DIR::LEFT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::MONSTER, 2150.f, 400.f, DIR::LEFT);


	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::MONSTER, 2500.f, 400.f, DIR::LEFT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::SPIDER, 1350.f, 140.f, DIR::DOWN);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BAT, 1200.f, 140.f, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BAT, 1230.f, 190.f, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::DOG, 4800, 1070, DIR::LEFT);

	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BEE, 1000, 1050, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BEE, 1200, 1000, DIR::RIGHT);



	/*ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BIRD, 600, 1050, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BIRD, 2200, 1000, DIR::RIGHT);
	ObjPoolManager::GetInstance()->SpawnMonster(MONSTER::BIRD, 2200, 1000, DIR::RIGHT);*/
	

	//end_line = { (long)3000.f, (long)320 };
	BmpManager::GetInstance()->InsertBmp(L"../Image/round1_1.bmp", L"round1");
	BmpManager::GetInstance()->InsertBmp(L"../Image/round1_2.bmp", L"round2");
	BmpManager::GetInstance()->InsertBmp(L"../Image/round1_3.bmp", L"round3");
	BmpManager::GetInstance()->InsertBmp(L"../Image/round1_4.bmp", L"round4");


	SoundManager::Get_Instance()->PlayBGM(L"stage1.wav", 7);
}

int Stage1::Update(void)
{
	KeyInput();
	MapScroll();
	//OffSet();
	
	LineManager::GetInstance()->Update();
	ObjManager::GetInstance()->Update();

	return 0;
}


void Stage1::LateUpdate(void)
{
	LineManager::GetInstance()->LateUpdate();
	ObjManager::GetInstance()->LateUpdate();
	DataManager::GetInstance()->LateUpdate();

	UpdateSavePoint();

	if (ObjManager::GetInstance()->GetPlayerInfo().x >= 7950.f &&
		ObjManager::GetInstance()->GetPlayerInfo().y <= 1200.f)
	{
		//BmpManager::GetInstance()->Release();
		SoundManager::Get_Instance()->StopAll();
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE2);
	}
	//CheckEndLine();
	CheckState();
}

void Stage1::Render(HDC dc)
{
		float x = ScrollManager::GetInstance()->GetScrollX();
		float y = ScrollManager::GetInstance()->GetScrollY();

		drawing_dc = BmpManager::GetInstance()->FindImage(L"round1");
		GdiTransparentBlt(dc, (int)x, (int)y+ 50 , 2000, 1568, drawing_dc, 0, 0, 1000, 784, RGB(255, 255, 255));

		drawing_dc = BmpManager::GetInstance()->FindImage(L"round2");
		GdiTransparentBlt(dc, (int)x+2000, (int)y + 50, 2000, 1568, drawing_dc, 0, 0, 1000, 784, RGB(255, 255, 255));

		drawing_dc = BmpManager::GetInstance()->FindImage(L"round3");
		GdiTransparentBlt(dc, (int)x+4000, (int)y + 50, 2000, 1568, drawing_dc, 0, 0, 1000, 784, RGB(255, 255, 255));

		drawing_dc = BmpManager::GetInstance()->FindImage(L"round4");
		GdiTransparentBlt(dc, (int)x+6000, (int)y + 50, 2000, 1568, drawing_dc, 0, 0, 1096, 784, RGB(255, 255, 255));

	if (m_result == GAME::NONE)
	{

		// 앞에는 그릴 곳, 오른쪽은 원하는 이미지 사이즈
		//GdiTransparentBlt(dc, (int)x, 0, 4096, 600, drawing_dc, 0, 0, 4096, 600, RGB(255, 255, 255));
		//BitBlt(dc, 0 + x , 0, WINCX, WINCY, drawing_dc, 0, 0, SRCCOPY);

	//	LineManager::GetInstance()->Render(dc);
		ObjManager::GetInstance()->Render(dc);

		RenderData(dc);
	}
	else
		Result(dc);


}

void Stage1::Release(void)
{
	ScrollManager::GetInstance()->Release();
	LineManager::GetInstance()->Release();
	ObjManager::GetInstance()->Release();
	save_point.erase(save_point.begin(), save_point.end());
	save_point.clear();

}

void Stage1::MapScroll(void)	// 스테이지1 로 이사		// 플레이어의 이동만큼 다른 물체도 이동시키는 함수
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
			-7200 < ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
			ScrollManager::GetInstance()->SetScrollX(-13.f);
		else if (-7201 == ScrollManager::GetInstance()->GetScrollX() &&
			in_the_cave == false)
		{
			ScrollManager::GetInstance()->SetScrollX2(0);
			ScrollManager::GetInstance()->InitScrollX(-7200);
		}

	}

	// 캐릭터 이동 먼저 -> 스크롤 동굴로 이동 
	// 1번 동굴 들어가기 4000 4200
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 4000 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 4200 &&
		in_the_cave == false)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-1200.f);
			ScrollManager::GetInstance()->SetScrollY2(0.f);

			ObjManager::GetInstance()->SetPlayerPos(1750, 0.f);

			in_the_cave = true;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}

	 // 1번 동굴 내부
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 1000 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 1400 &&
		in_the_cave == true )
		ScrollManager::GetInstance()->SetScrollX2(-1000.f);
	else if (ObjManager::GetInstance()->GetPlayerInfo().x > 1500 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 1800 &&
		in_the_cave == true)
	{
		ScrollManager::GetInstance()->SetScrollX2(-1200.f);
	}

	// 1번 동굴 나오기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 1700 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 1800 &&
		in_the_cave == true)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-3500.f);
			ScrollManager::GetInstance()->SetScrollY2(-1070.f);

			ObjManager::GetInstance()->SetPlayerPos(4050, 1070.f);

			in_the_cave = false;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}
	
	// 2번 동굴 들어가기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 6600 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 6670 &&
		in_the_cave == false)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-3150.f);
			ScrollManager::GetInstance()->SetScrollY2(-10.f);

			ObjManager::GetInstance()->SetPlayerPos(3520, 1.f);

			in_the_cave = true;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}

	// 2번 동굴 나오기
	if (ObjManager::GetInstance()->GetPlayerInfo().x > 3000 &&
		ObjManager::GetInstance()->GetPlayerInfo().x < 4030 &&
		in_the_cave == true)
	{
		if (KeyManager::GetInstance()->KeyDown('Z'))
		{
			ScrollManager::GetInstance()->SetScrollX2(-6300.f);
			ScrollManager::GetInstance()->SetScrollY2(-800.f);

			ObjManager::GetInstance()->SetPlayerPos(6650, 1100.f);

			in_the_cave = false;
			//ScrollManager::GetInstance()->InitScrollY(-6);

		}
	}
	// 올라타고 내려가기 만들기

	// 상하 스크롤
	if (ObjManager::GetInstance()->GetPlayerInfo().y >= -1600 || ObjManager::GetInstance()->GetPlayerInfo().y <= 1600)
	{
		
		 
		if (ObjManager::GetInstance()->GetPlayerInfo().x >2000 && ObjManager::GetInstance()->GetPlayerInfo().y  > 1400 && ScrollManager::GetInstance()->GetScrollY() > -1050)
			ScrollManager::GetInstance()->SetScrollY2(-1070);

		else if (ObjManager::GetInstance()->GetPlayerInfo().x <2100 && ObjManager::GetInstance()->GetPlayerInfo().y  > 1300 && ScrollManager::GetInstance()->GetScrollY() == -1070)
		{
			ScrollManager::GetInstance()->SetScrollY2(-1000.f);
		}
		
		if(ObjManager::GetInstance()->GetPlayerInfo().x >2000 && ObjManager::GetInstance()->GetPlayerInfo().x <3100 
			&& ObjManager::GetInstance()->GetPlayerInfo().y < 1300 && ScrollManager::GetInstance()->GetScrollY() == -1070)
			ScrollManager::GetInstance()->SetScrollY2(-900);

		 if(ObjManager::GetInstance()->GetPlayerInfo().x >2800 && ObjManager::GetInstance()->GetPlayerInfo().x <3300
			&& ObjManager::GetInstance()->GetPlayerInfo().y < 1100 && ScrollManager::GetInstance()->GetScrollY() == -900)
			ScrollManager::GetInstance()->SetScrollY2(-600);
		
		 else if (ObjManager::GetInstance()->GetPlayerInfo().x >2800 && ObjManager::GetInstance()->GetPlayerInfo().x <3100
			 && ObjManager::GetInstance()->GetPlayerInfo().y > 1150 && ScrollManager::GetInstance()->GetScrollY() == -600)
			 ScrollManager::GetInstance()->SetScrollY2(-900);
	
		 if (ObjManager::GetInstance()->GetPlayerInfo().x >3300 && ObjManager::GetInstance()->GetPlayerInfo().x <3650
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1150 && ScrollManager::GetInstance()->GetScrollY() == -600)
			 ScrollManager::GetInstance()->SetScrollY2(-850);

		 if (ObjManager::GetInstance()->GetPlayerInfo().x >2800 && ObjManager::GetInstance()->GetPlayerInfo().x <3650
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1100 && ScrollManager::GetInstance()->GetScrollY() == -850)
			 ScrollManager::GetInstance()->SetScrollY2(-600);

		 else if (ObjManager::GetInstance()->GetPlayerInfo().x >3600 && ObjManager::GetInstance()->GetPlayerInfo().x <3650
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1200 && ScrollManager::GetInstance()->GetScrollY() == -850)
			 ScrollManager::GetInstance()->SetScrollY2(-1070);


		 if(ObjManager::GetInstance()->GetPlayerInfo().x >4850 && ObjManager::GetInstance()->GetPlayerInfo().x <7050
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1200 && ScrollManager::GetInstance()->GetScrollY() == -1070)
			 ScrollManager::GetInstance()->SetScrollY2(-800);

		 if (ObjManager::GetInstance()->GetPlayerInfo().x >6650 && ObjManager::GetInstance()->GetPlayerInfo().x <7050
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1200 && ScrollManager::GetInstance()->GetScrollY() <= -1070)
			 ScrollManager::GetInstance()->SetScrollY2(-800);

	/*	 if (ObjManager::GetInstance()->GetPlayerInfo().x >7000 && ObjManager::GetInstance()->GetPlayerInfo().x <7500
			 && ObjManager::GetInstance()->GetPlayerInfo().y < 1200 && ScrollManager::GetInstance()->GetScrollY() == -800)
			 ScrollManager::GetInstance()->SetScrollY2(-1000);*/

	}

}