#pragma once
#include "include.h"

class Obj;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

public:
	static void	CollisionRectEx(list<Obj*> dest_, list<Obj*> src_);
	static void	CollisionRectPush(list<Obj*> dest_, list<Obj*> src_);
	static bool CollisionRectList(float& _y, RECT dest_, list<Obj*> src_);

private:
	static bool CheckRect(Obj* dest_, Obj* src_, float* width_, float* height_);

};

