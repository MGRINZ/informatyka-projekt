#include "BlocksVector.h"

Block* BlocksVector::getSolidBlockAtPosition(int x, int y)
{
	for (auto &block : *this)
	{
		Vector2f blockPosition = block.getPosition();
		if (blockPosition.x == x * Block::WIDTH && blockPosition.y == y * Block::WIDTH)
			return &block;
	}
	return nullptr;
}