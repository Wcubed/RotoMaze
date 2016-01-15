#ifndef AGENT_H
#define AGENT_H

#include "ofMain.h"

#include "Maze.h"

class Agent
{
public:
    Agent();
    Agent(Maze* _maze, ofPoint _mazePos, int _screenSize, bool enemy);

    void update(double dt, float gravAngle);
    void draw();

    void setScreenPos(ofPoint newPos);
    void setMazePos(ofPoint newPos);

    ofPoint getScreenPos() { return ofPoint(screenPos); }
    ofPoint getMazePos() { return ofPoint(mazePos); }

private:
    bool collidesWithBlock(ofPoint myScreenPos, ofPoint blockmazePos);

    ofPoint toScreenSpace(ofPoint pos);
    ofPoint toMazeSpace(ofPoint pos);

private:
    Maze* maze;

    ofPoint screenPos; // The position on screen.
    ofPoint mazePos; // The block position in the maze.

    ofVec2f vel; // Speed.

    int radius;
    int maxSpeed; // Maximum speed at which the agent can roll.

    int mazeSize;
    int screenSize;
    float blockSize;
    float halfBSize;

    bool horCol;
    bool verCol;
    bool corCol;

    bool isEnemy;

    static const bool debug = false;
};

#endif // AGENT_H
