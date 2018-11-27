#pragma once

#include <vector>
#include "Block.h"

class BlocksVector : public vector<Block>
{
public:
	Block* getSolidBlockAtPosition(int x, int y);
};
