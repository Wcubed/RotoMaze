#ifndef MAZE_H
#define MAZE_H

#include "ofMain.h"

#include "Block.h"
#include "Action.h"
#include "PriorityQueue.hpp"


/*
 * A grid of blocks which can preform searches on itself in accordance with the current direcion of gravity.
 */
class Maze
{
public:
    Maze();

    void update();
    void draw(int drawSize);

    Block* astarSearch(int originX, int originY);
    void updatePaths(int x, int y);

    // Setters.

    void setAngle(float _angle) { angle = _angle; }

    // Getters.

    int getSize() { return size; }
    bool isSolid(int x, int y);
    bool isStandable(int x, int y);

private:
    void createActions();
    bool isActionFeasible(Action action, ofPoint origin, float gravAngle, bool mirrored);

public:
    static const int size = 20; // Size (in blocks) of the maze.

private:
    float angle; // How much the maze is rotated. Most important for gravity.

    ofPoint target;

    Block blocks[size][size]; // Grid of blocks.

    vector<Action> actions; // List of all the actions an agent can take.

    // Search related.
    PriorityQueue<Block*, CompareBlocksAstar> astarQueue;
};

#endif // MAZE_H
