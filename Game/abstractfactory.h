#pragma once
#ifndef ABSTRACTFACTORY_H_
#define ABSTRACTFACTORY_H_

#include "obj.h"
#include "include.h"
// 추상화 클래스, 이 부분은 원하는 대로 커스터마이징 하면 됨.

template<typename T>  // 클래스 템플릿
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