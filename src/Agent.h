#ifndef AGENT_H
#define AGENT_H

#include "ofMain.h"

#include "Maze.h"

class Agent
{
public:
    Agent();
    Agent(Maze* _maze, ofPoint _mazePos, int _screenSize);

    void update(double dt, float angle);
    void draw();

    void setScreenPos(ofPoint newPos);
    void setMazePos(ofPoint newPos);

private:
    bool collidesWithBlock(ofPoint pos);

    ofPoint toScreenSpace(ofPoint pos);

private:
    Maze* maze;

    ofPoint screenPos; // The position on screen.
    ofPoint mazePos; // The block position in the maze.

    ofVec2f vel; // Speed.

    int size;

    int mazeSize;
    int screenSize;
    float blockSize;
};

#endif // AGENT_H
