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


	void		DeleteID(OBJ::ID id);				 // id 지우기
	void		AddObject(OBJ::ID id_, Obj* obj_); // 오브젝트 추가,  objid, objmanger 

public:
	list<Obj*>		m_objlist[OBJ::OBJ_END];		//ojbid를 담는 objmanager 리스트 멤버변수

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
	// 클래스와 전역변수의 생성 시점이 다르기 때문에 static으로 함수 생성
	static ObjManager*	GetInstance(void)		// 인스턴스 얻어오는 함수
	{
		if (nullptr == m_instance)				// 인스턴스가 null이라면
			m_instance = new ObjManager;		// 인스턴스화

		return m_instance;						// 인스턴스 반환
	}

	static void	DestroyInstance()				// 인스턴스 지우는 함수
	{
		if (nullptr != m_instance)				// 인스턴스가 null이 아니라면
		{
			delete m_instance;					// 인스턴스 삭제
			m_instance = nullptr;				// null 초기화
		}
	}

};

#endif // !OBJ_MANAGER_H_
