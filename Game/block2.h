#pragma once
#ifndef INVISIBLE_BLOCK_H_
#define INVISIBLE_BLOCK_H_
#endif // !INVISIBLE_BLOCK_H_

#include "block.h"

class InvisibleBlock : public Block			// 가려진 블록, 망치로 내려치면 보여지는 발판 
{
public:
	InvisibleBlock();
	~InvisibleBlock();
};

