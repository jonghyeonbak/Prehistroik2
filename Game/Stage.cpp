#include "stdafx.h"
#include "stage.h"
#include "abstractfactory.h"
#include "player.h"
#include "manager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Result(HDC _hdc)
{
	switch (m_result) {
	case GAME::CLEAR:
		if (m_scene_num + 1 != GAME::ID_END)
		{
			SetGameNum(GAME::ID((int)m_scene_num + 1));
			DataManager::GetInstance()->GetScore();
			DataManager::GetInstance()->SetScore(DataManager::GetInstance()->GetScore());
		}
		else
			SetGameNum(GAME::STAGEONE);
		break;
	case GAME::FAIL:
		BmpManager::GetInstance()->Release();
		SoundManager::Get_Instance()->StopAll();
		SceneManager::GetInstance()->SceneChange(SCENE_GAME_OVER);
		//ShowLose();
		//SetGameNum(GAME::STAGEONE);
		break;
	}
}


void Stage::Initialize(void)
{
	BmpManager::GetInstance()->InsertBmp(L"../Image/MapUi.bmp", L"MapUi");
	BmpManager::GetInstance()->InsertBmp(L"../Image/MapUi_Name1.bmp", L"MapUi_Name1");
	BmpManager::GetInstance()->InsertBmp(L"../Image/MapUi_Name2.bmp", L"MapUi_Name2");
	BmpManager::GetInstance()->InsertBmp(L"../Image/Life_Face.bmp", L"Life_Face");
	BmpManager::GetInstance()->InsertBmp(L"../Image/X.bmp", L"X");
	BmpManager::GetInstance()->InsertBmp(L"../Image/Energy.bmp", L"Energy");

	BmpManager::GetInstance()->InsertBmp(L"../Image/0.bmp", L"0");
	BmpManager::GetInstance()->InsertBmp(L"../Image/1.bmp", L"1");
	BmpManager::GetInstance()->InsertBmp(L"../Image/2.bmp", L"2");
	BmpManager::GetInstance()->InsertBmp(L"../Image/3.bmp", L"3");
	BmpManager::GetInstance()->InsertBmp(L"../Image/4.bmp", L"4");
	BmpManager::GetInstance()->InsertBmp(L"../Image/5.bmp", L"5");
	BmpManager::GetInstance()->InsertBmp(L"../Image/6.bmp", L"6");
	BmpManager::GetInstance()->InsertBmp(L"../Image/7.bmp", L"7");
	BmpManager::GetInstance()->InsertBmp(L"../Image/8.bmp", L"8");
	BmpManager::GetInstance()->InsertBmp(L"../Image/9.bmp", L"9");


}

int Stage::Update(void)
{
	if (DataManager::GetInstance()->GetLife() == 0
		&& DataManager::GetInstance()->GetEnergy() == 0)
		is_fail = true;

	ObjManager::GetInstance()->Update();

	return 0;
}

void Stage::LateUpdate(void)
{
	ObjManager::GetInstance()->LateUpdate();
}

void Stage::CheckState()
{
	if (is_clear)
	{
		SetResult(GAME::CLEAR);
	}

	else if (is_fail)
	{
		DataManager::GetInstance()->Release();
		SetResult(GAME::FAIL);
	}
}

void Stage::KeyInput()
{
#ifdef _DEBUG
	if (KeyManager::GetInstance()->KeyDown(VK_F1))
		is_clear = true;

	if (KeyManager::GetInstance()->KeyDown(VK_F2))
	{
		is_fail = true;
		BmpManager::GetInstance()->Release();
		SoundManager::Get_Instance()->StopAll();
		SceneManager::GetInstance()->SceneChange(SCENE_GAME_OVER);
	}
	if (KeyManager::GetInstance()->KeyDown(VK_F3))
		DataManager::GetInstance()->AddEnergy(1);

	if (KeyManager::GetInstance()->KeyDown(VK_F4))
		DataManager::GetInstance()->AddLife(1);

	if (KeyManager::GetInstance()->KeyDown(VK_F6))
		DataManager::GetInstance()->AddLife(-1);

	if (KeyManager::GetInstance()->KeyDown(VK_F7))
		DataManager::GetInstance()->AddScore(100000);

	//if (KeyManager::GetInstance()->KeyDown(VK_F8))
		//Set_Player_To_SavePoint();

	if (KeyManager::GetInstance()->KeyPressing('1'))
	{
		ScrollManager::GetInstance()->SetScrollX(5.0f);
	}
	if (KeyManager::GetInstance()->KeyPressing('3'))
	{
		ScrollManager::GetInstance()->SetScrollX(-5.0f);
	}
	if (KeyManager::GetInstance()->KeyPressing('2'))
	{
		ScrollManager::GetInstance()->SetScrollY(5.0f);
	}
	if (KeyManager::GetInstance()->KeyPressing('4'))
	{
		ScrollManager::GetInstance()->SetScrollY(-5.0f);
	}
	if (KeyManager::GetInstance()->KeyPressing('5'))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE1);
	}
	if (KeyManager::GetInstance()->KeyPressing('6'))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE2);
	}
	if (KeyManager::GetInstance()->KeyPressing('7'))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_STAGE3);
	}
#endif // DEBUG

}

void Stage::RenderData(HDC dc)
{


	//float x = ScrollManager::GetInstance()->GetScrollX();

	ObjManager::GetInstance()->Render(dc);

	drawing_dc = BmpManager::GetInstance()->FindImage(L"MapUi");
	GdiTransparentBlt(dc, 0, 535, 800, 70, drawing_dc, 0, 0, 800, 70, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"MapUi_Name1");
	GdiTransparentBlt(dc, 5, 535, 304, 15, drawing_dc, 0, 0, 304, 15, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"MapUi_Name2");
	GdiTransparentBlt(dc, 505, 535, 89, 15, drawing_dc, 0, 0, 89, 15, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"Life_Face");
	GdiTransparentBlt(dc, -13, 528, 80, 80, drawing_dc, 0, 0, 80, 80, RGB(255, 255, 255));

	drawing_dc = BmpManager::GetInstance()->FindImage(L"X");
	GdiTransparentBlt(dc, 57, 563, 18, 18, drawing_dc, 0, 0, 18, 18, RGB(255, 255, 255));

	// lifes
	if (DataManager::GetInstance()->GetLife() == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	if (DataManager::GetInstance()->GetLife() == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	if (DataManager::GetInstance()->GetLife() == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	if (DataManager::GetInstance()->GetLife() == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	if (DataManager::GetInstance()->GetLife() >= 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 80, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// energy
	if (DataManager::GetInstance()->GetEnergy() == 3 ||
		DataManager::GetInstance()->GetEnergy() == 2 ||
		DataManager::GetInstance()->GetEnergy() == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"Energy");
		GdiTransparentBlt(dc, 480, 545, 60, 60, drawing_dc, 0, 0, 60, 60, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetEnergy() == 3 ||
		DataManager::GetInstance()->GetEnergy() == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"Energy");
		GdiTransparentBlt(dc, 525, 545, 60, 60, drawing_dc, 0, 0, 60, 60, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetEnergy() == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"Energy");
		GdiTransparentBlt(dc, 570, 545, 60, 60, drawing_dc, 0, 0, 60, 60, RGB(255, 255, 255));
	}

	if (DataManager::GetInstance()->GetLife() == 0 &&
		DataManager::GetInstance()->GetEnergy() == 0)
		is_fail = true;

	//score 
	// 7번째 자리
	if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if(int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.000001) % 2 == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 160, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 6번째 자리
	if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.00001) % 10 == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 198, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 5번째 자리
	if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() * 0.0001) % 10 == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 236, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 4번째 자리
	if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10000 * 0.001) == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 274, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 3번째 자리
	if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) ==8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 1000 * 0.01) ==9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 312, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 2번째 자리
	if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 100 * 0.1) == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 350, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}

	// 1번째 자리
	if (int(DataManager::GetInstance()->GetScore() % 10) == 0)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"0");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 1)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"1");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 2)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"2");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 3)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"3");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 4)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"4");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 5)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"5");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 6)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"6");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 7)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"7");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 8)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"8");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
	else if (int(DataManager::GetInstance()->GetScore() % 10) == 9)
	{
		drawing_dc = BmpManager::GetInstance()->FindImage(L"9");
		GdiTransparentBlt(dc, 388, 555, 35, 35, drawing_dc, 0, 0, 35, 35, RGB(255, 255, 255));
	}
}

void Stage::SetPlayerToSavePoint()
{
	if (save_point.empty())
		return;

	ObjManager::GetInstance()->SetPlayerInit();
	ObjManager::GetInstance()->SetPlayerJump(false);
	ObjManager::GetInstance()->SetPlayerPos(save_point.front().x + PLAYER_POS_X, PLAYER_POS_Y);
	ScrollManager::GetInstance()->InitScrollX(-save_point.front().x);
}

void Stage::UpdateSavePoint()
{
	if (save_point.size() < 2)
		return;

	list<POINT>::iterator save = save_point.begin();
	if ((++save)->x < (-ScrollManager::GetInstance()->GetScrollX()))
	{
		save_point.pop_front();
	}
}

void Stage::CheckEndLine()
{
	if (end_line.x <= (-ScrollManager::GetInstance()->GetScrollX()))
	{
		is_clear = true;
	}
}

void Stage::Release(void)
{

}

void Stage::FallDown()
{
	if (ObjManager::GetInstance()->GetPlayerRECT().bottom > WINCY)
	{
		ObjManager::GetInstance()->SetPlayerDie(false);
		SetPlayerToSavePoint();
		DataManager::GetInstance()->AddLife(-1);
	}
}

void Stage::InitUi()
{
	//hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Cascadia Mono SemiBold")); // 폰트 제작
}