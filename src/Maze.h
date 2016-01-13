#ifndef MAZE_H
#define MAZE_H

#include "ofMain.h"

#include "Block.h"


/*
 * A grid of blocks which can preform searches on itself in accordance with the current direcion of gravity.
 */
class Maze
{
public:
    Maze();

    void update();
    void draw(int drawSize);

    void astarSearch();

    // Setters.

    void setAngle(float _angle) { angle = _angle; }

    // Getters.

    int getSize() { return size; }
    bool isSolid(int x, int y);
    bool isStandable(int x, int y);

private:
    float angle; // How much the maze is rotated. Most important for gravity.

    static const int size = 20; // Size (in blocks) of the maze.

    ofPoint target;

    Block blocks[size][size]; // Grid of blocks.
};

#endif // MAZE_H
