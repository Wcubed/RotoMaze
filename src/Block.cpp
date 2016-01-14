#include "Block.h"

Block::Block(int _x, int _y)
{
    x = _x;
    y = _y;

    pos = ofPoint(x, y);
}

