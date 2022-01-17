#include "stdafx.h"
#include "collision_manager.h"
#include "include.h"
#include "item.h"
#include "player.h"
#include "bullet.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::CollisionRectEx(list<Obj*> dest_, list<Obj*> src_)	// 플레이어, 몬스터 
{
	for (auto Dest : dest_)
	{
		float width = 0.f, height = 0.f;
		for (auto Src : src_)
		{
			if (Dest->GetDead() || Src->GetDead())
				continue;

			if (CheckRect(Dest, Src, &width, &height))
			{
				// 상하
				if (width > height)
				{
					if (Dest->GetInfo().y < Src->GetInfo().y)
					{
						Src->SetCollision(Dest, DIR::UP);
						Dest->SetCollision(Src, DIR::DOWN);
					}
					else
					{
						Src->SetCollision(Dest, DIR::DOWN);
						Dest->SetCollision(Src, DIR::UP);
					}
					
				}

				// 좌우
				else
				{
					if (Dest->GetInfo().x < Src->GetInfo().x)
					{
						Src->SetCollision(Dest, DIR::LEFT);
						Dest->SetCollision(Src, DIR::RIGHT);
					}
					else
					{
						Src->SetCollision(Dest, DIR::RIGHT);
						Dest->SetCollision(Src, DIR::LEFT);
					}
				}
			}
		}
	}
}

bool CollisionManager::CollisionRectList(float&  y_, RECT dest_, list<Obj*> src_)
{
	RECT rc{};
	for (auto Src : src_)
	{
		if (IntersectRect(&rc, &dest_, &Src->GetRect()))
		{
			y_ = Src->GetRect().top;
			return true;
		}
	}
	return false;
}

//void CollisionManager::CollisionRectPush(list<Obj*> dest_, list<Obj*> src_)
//{
//	for (auto Dest : dest_)
//	{
//		float width = 0.f, height = 0.f;
//		for (auto Src : src_)
//		{
//			if (CheckRect(Dest, Src, &width, &height))
//			{
//				// 상하
//				if (width > height)
//				{
//					if (Dest->GetInfo().y < Src->GetInfo().y)
//					{
//						Dest->SetPosY(Src->GetYSize());
//						//Dest->
//						//Src->SetPosY(height);
//					}
//					else
//					{
//						//Src->SetPosY(-height);
//						Dest->SetPosY(-height);
//					}
//				}
//
//				// 좌우
//				else
//				{
//					if (Dest->GetInfo().x < Src->GetInfo().x)
//					{
//						//Src->SetPosY(width);
//					}
//					else
//					{
//						//Src->SetPosY(-width);
//					}
//				}
//			}
//		}
//	}
//}

bool CollisionManager::CheckRect(Obj* pDest, Obj* pSrc, float* _pWidth, float* _pHeight)
{
	float width = abs(pDest->GetInfo().x - pSrc->GetInfo().x);
	float height = abs(pDest->GetInfo().y - pSrc->GetInfo().y);

	float cx = (pDest->GetInfo().cx + pSrc->GetInfo().cx) * 0.5f;
	float cy = (pDest->GetInfo().cy + pSrc->GetInfo().cy) * 0.5f;

	if (width < cx && height < cy)
	{
		*_pWidth = cx - width;
		*_pHeight = cy - height;
		return true;
	}

	else
		return false;
}