#pragma once
#ifndef OBJ_POOL_MANAGER_H_
#define OBJ_POOL_MANAGER_H_

#include "include.h"

class Obj;
class ObjPoolManager
{
private:
	static	ObjPoolManager* m_instance;

private:
	vector<Obj*> monster_pool[MONSTER::MONSTER_END];
	vector<Obj*> bullet_pool[BULLET::BULLET_END];
	vector<Obj*> item_pool[ITEM::ITEM_END]; 
	vector<Obj*> obstacle_pool[BLOCK::BLOCK_END];
	vector<Obj*> obstacle_pool2[OBSTACLE::OBSTACLE_END];

private:
	ObjPoolManager();
	~ObjPoolManager();

public:
	void	Release();

public:                        
	void	SpawnMonster(MONSTER::ID _monster, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	SpawnBullet(BULLET::ID _bullet, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	SpawnItem(ITEM::ID _item, float _X, float _Y, DIR::DIR _dir = DIR::RIGHT);
	void	SpawnObstacle(BLOCK::ID _item, float _X, float _Y);
	void	SpawnObstacle2(OBSTACLE::ID _item, float _X, float _Y);

public:
	//void	LoadObstacles(const TCHAR* _file);

public:
	static ObjPoolManager* GetInstance()
	{
		if (!m_instance)
			m_instance = new ObjPoolManager;

		return m_instance;
	}

	static void	DestroyInstance()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

};

#endif // !OBJ_POOL_MANAGER_H_
