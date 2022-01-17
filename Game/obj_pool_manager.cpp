#include "stdafx.h"
#include "Obj.h"
#include "obj_pool_manager.h"
#include "Obj_manager.h"
#include "abstractfactory.h"
#include "bullet.h"
#include "block.h"
#include "food.h"
#include "monster.h"
#include "save.h"
#include "food_file.h"
#include "monster_file.h"
ObjPoolManager* ObjPoolManager::m_instance = nullptr;

ObjPoolManager::ObjPoolManager()
{
}


ObjPoolManager::~ObjPoolManager()
{
}

void ObjPoolManager::Release()
{
	for (int i = 0; i < MONSTER::MONSTER_END; ++i)
	{
		for_each(monster_pool[i].begin(), monster_pool[i].end(), DeleteObj());
		monster_pool[i].clear();
	}

	for (int i = 0; i < BULLET::BULLET_END; ++i)
	{
		for_each(bullet_pool[i].begin(), bullet_pool[i].end(), DeleteObj());
		bullet_pool[i].clear();
	}

	for (int i = 0; i < ITEM::ITEM_END; ++i)
	{
		for_each(item_pool[i].begin(), item_pool[i].end(), DeleteObj());
		item_pool[i].clear();
	}

	for (int i = 0; i < BLOCK::BLOCK_END; ++i)
	{
		for_each(obstacle_pool[i].begin(), obstacle_pool[i].end(), DeleteObj());
		obstacle_pool[i].clear();
	}


	for (int i = 0; i < OBSTACLE::OBSTACLE_END; ++i)
	{
		for_each(obstacle_pool[i].begin(), obstacle_pool[i].end(), DeleteObj());
		obstacle_pool[i].clear();
	}

}

void ObjPoolManager::SpawnMonster(MONSTER::ID _monster, float _X, float _Y, DIR::DIR _dir)
{
	for (auto& iter : monster_pool[_monster])
	{
		if (iter->GetDead())
		{
			iter->Initialize();
			iter->SetPos(_X, _Y);
			iter->SetDirection(_dir);
			iter->SetDead(false);
			iter->UpdateRect();
			ObjManager::GetInstance()->AddObject(OBJ::MONSTER, iter);
			return;
		}
	}

	switch (_monster)
	{
	case MONSTER::MONSTER:
		monster_pool[_monster].push_back(AbstractFactory<Monster>::Create(_X, _Y, _dir));
		break;
	case MONSTER::SNAKE:
		monster_pool[_monster].push_back(AbstractFactory<Snake>::Create(_X, _Y, _dir));
		break;
	case MONSTER::BEE:
		monster_pool[_monster].push_back(AbstractFactory<Bee>::Create(_X, _Y, _dir));
		break;
	case MONSTER::BAT:
		monster_pool[_monster].push_back(AbstractFactory<Bat>::Create(_X, _Y, _dir));
		break;
	case MONSTER::DINO:
		monster_pool[_monster].push_back(AbstractFactory<Dino>::Create(_X, _Y, _dir));
		break;
	case MONSTER::HUMAN:
		monster_pool[_monster].push_back(AbstractFactory<Human>::Create(_X, _Y, _dir));
		break;
	case MONSTER::DOG:
		monster_pool[_monster].push_back(AbstractFactory<Dog>::Create(_X, _Y, _dir));
		break;
	case MONSTER::SPIDER:
		monster_pool[_monster].push_back(AbstractFactory<Spider>::Create(_X, _Y, _dir));
		break;
	case MONSTER::BIRD:
		monster_pool[_monster].push_back(AbstractFactory<Bird>::Create(_X, _Y, _dir));
		break;
	case MONSTER::OLD_BIRD:
		monster_pool[_monster].push_back(AbstractFactory<OldBird>::Create(_X, _Y, _dir));
		break;
	default:
		return;
	}

	ObjManager::GetInstance()->AddObject(OBJ::MONSTER, monster_pool[_monster].back());

}

void ObjPoolManager::SpawnBullet(BULLET::ID _bullet, float _X, float _Y, DIR::DIR _dir)
{
	for (auto& iter : bullet_pool[_bullet])
	{
		if (iter->GetDead())
		{
			iter->SetPos(_X, _Y);
			iter->Initialize();
			iter->SetDirection(_dir);
			iter->UpdateRect();
			iter->SetDead(false);
			ObjManager::GetInstance()->AddObject(OBJ::BULLET, iter);
			return;
		}
	}

	switch (_bullet)
	{
	case BULLET::HAMMER:
		bullet_pool[_bullet].push_back(AbstractFactory<Bullet>::Create(_X, _Y, _dir));
		break;
	default:
		return;
	}

	ObjManager::GetInstance()->AddObject(OBJ::BULLET, bullet_pool[_bullet].back());
}

void ObjPoolManager::SpawnItem(ITEM::ID _item, float _X, float _Y, DIR::DIR _dir)
{
	for (auto& i : item_pool[_item])
	{
		if (i->GetDead())
		{
			i->Initialize();
			i->SetPos(_X, _Y);
			i->SetDirection(_dir);
			i->UpdateRect();
			i->SetDead(false);
			ObjManager::GetInstance()->AddObject(OBJ::ITEM, i);
			return;
		}
	}

	switch (_item)
	{
	case ITEM::FOOD:
		item_pool[_item].push_back(AbstractFactory<Food>::Create(_X, _Y));
		break;
	case ITEM::GRAPE:
		item_pool[_item].push_back(AbstractFactory<Grape>::Create(_X, _Y));
		break;
	case ITEM::CANDY:
		item_pool[_item].push_back(AbstractFactory<Candy>::Create(_X, _Y));
		break;
	case ITEM::CAKE:
		item_pool[_item].push_back(AbstractFactory<Cake>::Create(_X, _Y));
		break;
	case ITEM::BEER:
		item_pool[_item].push_back(AbstractFactory<Beer>::Create(_X, _Y));
		break;
	case ITEM::CANDLE:
		item_pool[_item].push_back(AbstractFactory<Candle>::Create(_X, _Y));
		break;
	case ITEM::CANDLE2:
		item_pool[_item].push_back(AbstractFactory<Candle2>::Create(_X, _Y));
		break;
	case ITEM::HEART:
		item_pool[_item].push_back(AbstractFactory<Heart>::Create(_X, _Y));
		break;
	case ITEM::GOLD:
		item_pool[_item].push_back(AbstractFactory<Gold>::Create(_X, _Y));
		break;
	case ITEM::CHOCO:
		item_pool[_item].push_back(AbstractFactory<Choco>::Create(_X, _Y));
		break;
	case ITEM::CHERRY:
		item_pool[_item].push_back(AbstractFactory<Cherry>::Create(_X, _Y));
		break;
	case ITEM::EGG:
		item_pool[_item].push_back(AbstractFactory<Egg>::Create(_X, _Y));
		break;
	case ITEM::DOUGHNUT:
		item_pool[_item].push_back(AbstractFactory<Doughnut>::Create(_X, _Y));
		break;
	case ITEM::DEATH:
		item_pool[_item].push_back(AbstractFactory<Death>::Create(_X, _Y));
		break;
	case ITEM::SCORE750:
		item_pool[_item].push_back(AbstractFactory<score750>::Create(_X, _Y));
		break;
	case ITEM::SCORE20000:
		item_pool[_item].push_back(AbstractFactory<Score20000>::Create(_X, _Y));
		break;
	case ITEM::BANANA:
		item_pool[_item].push_back(AbstractFactory<Banana>::Create(_X, _Y));
		break;
	case ITEM::PAPRIKA:
		item_pool[_item].push_back(AbstractFactory<Paprika>::Create(_X, _Y));
		break;
	case ITEM::LIFEUP:
		item_pool[_item].push_back(AbstractFactory<Lifeup>::Create(_X, _Y));
		break;
	case ITEM::EXE:
		item_pool[_item].push_back(AbstractFactory<Exe>::Create(_X, _Y));
		break;
	case ITEM::GAMEOVER:
		item_pool[_item].push_back(AbstractFactory<Gameover>::Create(_X, _Y));
		break;
	case ITEM::LEAMON:
		item_pool[_item].push_back(AbstractFactory<Lemon>::Create(_X, _Y));
		break;
	case ITEM::CANDY2:
		item_pool[_item].push_back(AbstractFactory<Candy2>::Create(_X, _Y));
		break;
	case ITEM::ICECREAM:
		item_pool[_item].push_back(AbstractFactory<Icecream>::Create(_X, _Y));
		break;
	case ITEM::ICECREAM2:
		item_pool[_item].push_back(AbstractFactory<Icecream2>::Create(_X, _Y));
		break;
	case ITEM::PUDDING:
		item_pool[_item].push_back(AbstractFactory<Pudding>::Create(_X, _Y));
		break;
	case ITEM::MEAT:
		item_pool[_item].push_back(AbstractFactory<Meat>::Create(_X, _Y));
		break;
	default:
		return;
	}

	ObjManager::GetInstance()->AddObject(OBJ::ITEM, item_pool[_item].back());
}



void ObjPoolManager::SpawnObstacle(BLOCK::ID _item, float _X, float _Y)
{
	for (auto& i : obstacle_pool[_item])
	{
		if (i->GetDead())
		{
			i->Initialize();
			i->SetPos(_X, _Y);
			i->UpdateRect();
			i->SetDead(false);
			ObjManager::GetInstance()->AddObject(OBJ::OBSTACLE, i);
			return;
		}
	}

	switch (_item)
	{
	case BLOCK::DEFAULT:
		obstacle_pool[_item].push_back(AbstractFactory<Block>::Create(_X, _Y));
		break;
	default:
		return;
	}

	ObjManager::GetInstance()->AddObject(OBJ::OBSTACLE, obstacle_pool[_item].back());
}

void ObjPoolManager::SpawnObstacle2(OBSTACLE::ID _item, float _X, float _Y)
{
	for (auto& i : obstacle_pool[_item])
	{
		if (i->GetDead())
		{
			i->Initialize();
			i->SetPos(_X, _Y);
			i->UpdateRect();
			i->SetDead(false);
			ObjManager::GetInstance()->AddObject(OBJ::OBSTACLE, i);
			return;
		}
	}

	switch (_item)
	{
	case OBSTACLE::SAVE:
		obstacle_pool[_item].push_back(AbstractFactory<Save>::Create(_X, _Y));
		break;

	default:
		return;
	}

	ObjManager::GetInstance()->AddObject(OBJ::OBSTACLE, obstacle_pool[_item].back());
}


