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

    bool solid = false; // Is this a block or air.
    bool standable = false; // Can you stand here without falling.

    // Search related.
    bool visited;
    bool marked;
    float distToTarget; // Distance to the target of the search.
    float distFromOrigin; // Distance to here from the origin of the search.

    Block* parent; // Parent in the astar graph.

    // All the blocks that are reachable from this one.
    // The integer is the distance to that block.
    std::vector<BlockLink> links;
};

// Comparison function to use with astar priority queue.
class CompareBlocksAstar {
public:
    bool operator ()(Block* b1, Block* b2) const {
        return b1->distFromOrigin + b1->distToTarget*1.5 > b2->distFromOrigin + b2->distToTarget*1.5;
    }
};

#endif // BLOCK_H
