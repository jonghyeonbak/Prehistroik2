#pragma once
#ifndef OBJ_MANAGER_H_
#define OBJ_MANAGER_H_

#include "include.h"

class Obj;
class ObjManager
{
private:
	static ObjManager*			m_instance;

private:
	ObjManager();
	~ObjManager();

public:
	int			Update(void);
	void		LateUpdate(void);
	void		Render(HDC dc);
	void		Release(void);


	void		DeleteID(OBJ::ID id);				 // id �����
	void		AddObject(OBJ::ID id_, Obj* obj_); // ������Ʈ �߰�,  objid, objmanger 

public:
	list<Obj*>		m_objlist[OBJ::OBJ_END];		//ojbid�� ��� objmanager ����Ʈ �������

	list<Obj*>		GetObjList(OBJ::ID _id);
	const RECT&		GetPlayerRECT() const;
	const INFO&		GetPlayerInfo() const;
	const float&	GetPlayerSpeed() const;
	const bool&		GetPlayerVaild() const;
	void			SetPlayerInit();
	void			SetPlayerJump(bool _bool);
	void			SetPlayerPos(float _x, float _y);
	void			SetPlayerDie(bool _bool);
	const bool&		GetPlayerDie() const;
	
public:
	// Ŭ������ ���������� ���� ������ �ٸ��� ������ static���� �Լ� ����
	static ObjManager*	GetInstance(void)		// �ν��Ͻ� ������ �Լ�
	{
		if (nullptr == m_instance)				// �ν��Ͻ��� null�̶��
			m_instance = new ObjManager;		// �ν��Ͻ�ȭ

		return m_instance;						// �ν��Ͻ� ��ȯ
	}

	static void	DestroyInstance()				// �ν��Ͻ� ����� �Լ�
	{
		if (nullptr != m_instance)				// �ν��Ͻ��� null�� �ƴ϶��
		{
			delete m_instance;					// �ν��Ͻ� ����
			m_instance = nullptr;				// null �ʱ�ȭ
		}
	}

};

#endif // !OBJ_MANAGER_H_
