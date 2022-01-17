#pragma once
#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

#include "obj.h"
#include "include.h"
// �߻�ȭ Ŭ����, �� �κ��� ���ϴ� ��� Ŀ���͸���¡ �ϸ� ��.

template<typename T>  // Ŭ���� ���ø�
class AbstractFactory
{
public:
	AbstractFactory() {}
	~AbstractFactory() {}

public:
	static Obj*		Create()
	{
		Obj*	obj = new T;
		obj->Initialize();

		return obj;
	}

	static Obj*		Create(float fx_, float fy_, DIR::DIR dir_ = DIR::RIGHT)
	{
		Obj*	obj = new T;
		obj->SetPos(fx_, fy_);
		obj->Initialize();
		obj->SetDirection(dir_);
		obj->UpdateRect();

		return obj;
	}
};
#endif