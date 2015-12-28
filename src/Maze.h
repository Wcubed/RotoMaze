#ifndef MAZE_H
#define MAZE_H

#include "ofMain.h"

class Maze
{
public:
    Maze();

    void draw(int drawSize);

    void setAngle(float _angle) { angle = _angle; }

private:
    float angle; // How much the maze is rotated. Most important for gravity.

    static const int size = 20; // Size (in blocks) of the maze.

    bool maze[size][size]; // The actual maze.
};

#endif // MAZE_H
