#ifndef AGENT_H
#define AGENT_H

#include "ofMain.h"

class Agent
{
public:
    Agent();
    Agent(ofPoint _mazePos, int _mazeSize, int _screenSize);

    void update(double dt, float angle);
    void draw();

    void setScreenPos(ofPoint newPos);
    void setMazePos(ofPoint newPos);

private:
    ofPoint screenPos; // The position on screen.
    ofPoint mazePos; // The block position in the maze.

    int mazeSize;
    int screenSize;
};

#endif // AGENT_H
