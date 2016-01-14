#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <utility>

#include "ofMain.h"

class Block;

struct BlockLink {
    Block* block;
    int length;
};

class Block
{
public:
    Block() { x = 0; y = 0; }
    Block(int _x, int _y);

    int x, y;
    ofPoint pos;

    bool solid = false;
    bool standable = false;

    // All the blocks that are reachable from this one.
    // The integer is the distance to that block.
    std::vector<BlockLink> links;
};

#endif // BLOCK_H
