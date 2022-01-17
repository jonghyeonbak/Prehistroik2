#include "stdafx.h"
#include "obj.h"
#include "manager.h"
#include "player.h"

ObjManager*	ObjManager::m_instance = nullptr;

ObjManager::ObjManager()
{
}


ObjManager::~ObjManager()
{
}

void ObjManager::AddObject(OBJ::ID id_, Obj* obj_)
{
	//objlist 배열에 obj를 원소로 넣어라
	m_objlist[id_].push_back(obj_);
}

int ObjManager::Update(void)
{
	//objid의 처음부터 끝까지
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		// list의 첫 번째 원소를 iter에 저장
		auto& iter = m_objlist[i].begin();
		// list의 마지막 원소가 아니라면 계속 실행
		for (; iter != m_objlist[i].end(); )
		{
			// iter의 업데이트를 event에 대입
			int	event = (*iter)->Update();
			if (OBJ_DEAD == event) // 만약 event가 obj_dead라면
			{
				iter = m_objlist[i].erase(iter);	// 리스트의 iter 원소까지 모두 삭제 후 iter에 대입
													// 원소는 iter 뒤에 있는 것을 가리킴
			}
			else
				++iter;	// event가 obj_dead가 아니라면 iter 증가
		}
	}

	return 0;
}

void ObjManager::LateUpdate(void)
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)		// objid가 끝날 때 까지 실행
	{
		for (auto& iter : m_objlist[i])
		{
			iter->LateUpdate();

			if (m_objlist[i].empty())
				break;
		}
	}

	CollisionManager::CollisionRectEx(m_objlist[OBJ::PLAYER], m_objlist[OBJ::MONSTER]);
	CollisionManager::CollisionRectEx(m_objlist[OBJ::PLAYER], m_objlist[OBJ::ITEM]);
	CollisionManager::CollisionRectEx(m_objlist[OBJ::PLAYER], m_objlist[OBJ::OBSTACLE]);
	CollisionManager::CollisionRectEx(m_objlist[OBJ::BULLET], m_objlist[OBJ::MONSTER]);

	//CollisionManager::CollisionRectPush(m_objlist[OBJ::PLAYER], m_objlist[OBJ::OBSTACLE]);

	//CCollisionMgr::Collision_Sphere(m_ObjList[OBJID::BULLET], m_ObjList[OBJID::MONSTER]);
	//CCollisionMgr::Collision_RectEx(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTER]);
}

void ObjManager::Render(HDC m_dc)
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		for (auto& iter : m_objlist[i])
			iter->Render(m_dc);
	}
}

void ObjManager::Release(void)
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{

		m_objlist[i].clear();
	}
}

void ObjManager::DeleteID(OBJ::ID id)
{
	for (auto& iter : m_objlist[id])
		SafeDelete(iter);

	m_objlist[id].clear();
}

list<Obj*> ObjManager::GetObjList(OBJ::ID _id)
{
	return m_objlist[_id];
}

const RECT& ObjManager::GetPlayerRECT() const
{
	if (m_objlist[OBJ::PLAYER].empty())
		return{};

	return m_objlist[OBJ::PLAYER].front()->GetRect();
}

const INFO& ObjManager::GetPlayerInfo() const
{
	if (m_objlist[OBJ::PLAYER].empty())
		return{};

	return m_objlist[OBJ::PLAYER].front()->GetInfo();
}

const float& ObjManager::GetPlayerSpeed() const
{
	if (m_objlist[OBJ::PLAYER].empty())
		return{};

	return m_objlist[OBJ::PLAYER].front()->GetSpeed();
}

const bool& ObjManager::GetPlayerVaild() const
{
	if (m_objlist[OBJ::PLAYER].empty())
		return{};

	return m_objlist[OBJ::PLAYER].front()->GetVaild();
}

void ObjManager::SetPlayerInit()
{
	if (m_objlist[OBJ::PLAYER].empty())
		return;

	static_cast<Player*>(m_objlist[OBJ::PLAYER].front())->Initialize();
}

void ObjManager::SetPlayerJump(bool _bool)
{
	if (m_objlist[OBJ::PLAYER].empty())
		return;

	static_cast<Player*>(m_objlist[OBJ::PLAYER].front())->SetJump(false);
}

void ObjManager::SetPlayerPos(float _x, float _y)
{
	if (m_objlist[OBJ::PLAYER].empty())
		return;

	m_objlist[OBJ::PLAYER].front()->SetState(STATE::IDLE);
	m_objlist[OBJ::PLAYER].front()->SetPos(_x, _y);
	m_objlist[OBJ::PLAYER].front()->UpdateRect();
}

void ObjManager::SetPlayerDie(bool _bool)
{
	if (m_objlist[OBJ::PLAYER].empty())
		return;

	m_objlist[OBJ::PLAYER].front()->SetDead(_bool);
}

const bool& ObjManager::GetPlayerDie() const
{
	if (m_objlist[OBJ::PLAYER].empty())
		return false;

	if (m_objlist[OBJ::PLAYER].front()->GetDead())
		return true;

	return false;
}