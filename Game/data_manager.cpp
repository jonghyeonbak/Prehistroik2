#include "stdafx.h"
#include "data_manager.h"
#include "define.h"

DataManager* DataManager::m_instance = nullptr;

DataManager::DataManager()
	:energy(3), score(0000000.f), life(3), max_life(9)
{
}


DataManager::~DataManager()
{
}

void DataManager::Initialize()
{
	GetScore();
	GetLife();
	GetEnergy();
}
void DataManager::LateUpdate()
{
	if (life >= 1 && energy <= 0)
	{
		energy = 3;
		--life;
	}
	else
	{
		energy == 0;
		life == 0;
	}

	if (energy > 3)
	{
		energy = 3;
		
	}
}

void DataManager::Release()
{
	Initialize();
}
