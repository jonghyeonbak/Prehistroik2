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
	//objlist �迭�� obj�� ���ҷ� �־��
	m_objlist[id_].push_back(obj_);
}

int ObjManager::Update(void)
{
	//objid�� ó������ ������
	for (int i = 0; i < OBJ::OBJ_END; ++i)
	{
		// list�� ù ��° ���Ҹ� iter�� ����
		auto& iter = m_objlist[i].begin();
		// list�� ������ ���Ұ� �ƴ϶�� ��� ����
		for (; iter != m_objlist[i].end(); )
		{
			// iter�� ������Ʈ�� event�� ����
			int	event = (*iter)->Update();
			if (OBJ_DEAD == event) // ���� event�� obj_dead���
			{
				iter = m_objlist[i].erase(iter);	// ����Ʈ�� iter ���ұ��� ��� ���� �� iter�� ����
													// ���Ҵ� iter �ڿ� �ִ� ���� ����Ŵ
			}
			else
				++iter;	// event�� obj_dead�� �ƴ϶�� iter ����
		}
	}

	return 0;
}

void ObjManager::LateUpdate(void)
{
	for (int i = 0; i < OBJ::OBJ_END; ++i)		// objid�� ���� �� ���� ����
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