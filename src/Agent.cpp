#include "Agent.h"

/*
 * Default constructor, position will be 0, 0.
 */
Agent::Agent() {
    setMazePos(ofPoint(0, 0));
}

/*
 * Constructor with position.
 */
Agent::Agent(Maze* _maze, ofPoint _mazePos, int _screenSize)
{
    maze = _maze;

    mazePos = ofPoint(0, 0);
    screenPos = ofPoint(0, 0);

    mazeSize = maze->getSize();
    screenSize = _screenSize;

    blockSize = screenSize / mazeSize;
    size = blockSize;

    setMazePos(_mazePos);
}

/*
 * Updates the agent according to the angle of gravity.
 */
void Agent::update(double dt, float angle) {
    // Calculate the acceleration due to gravity.
    ofVec2f acc = ofVec2f(0, 9.81 * blockSize*0.5);
    acc.rotate(-angle);
    acc = acc * dt;

    // Update the new velocity.
    vel += acc;

    // Update the location with the speed.
    ofPoint newPos = ofPoint(screenPos);
    newPos += vel * dt;
    setScreenPos(newPos);
}

/*
 * Draws the agent at it's current location.
 */
void Agent::draw() {
    ofPushMatrix();
    ofPushStyle();

    ofTranslate(screenPos);
    ofSetColor(200, 0, 0, 255);
    ofFill();

    // Draw a circle with the size of a single block.
    ofDrawCircle(0, 0, size*0.5);

    ofPopStyle();
    ofPopMatrix();
}

/*
 * Sets the Agents position from a new screen position.
 * Updates the maze position accordingly.
 */
void Agent::setScreenPos(ofPoint newPos) {
    screenPos = newPos;

    // Calculate the maze position from the screen position.
    mazePos.set(int((mazeSize * screenSize)/screenPos.x), int((mazeSize * screenSize)/screenPos.y));
}

/*
 * Sets the Agents position from a new maze position.
 * Updates the screen position accordingly.
 */
void Agent::setMazePos(ofPoint newPos) {
    mazePos = newPos;

    // Calculate the screen position from the maze position.
    screenPos.set(toScreenSpace(newPos));
}

/*
 * Checks if the agent is colliding with a block.
 */
bool Agent::collidesWithBlock(ofPoint pos) {
    bool result;

    // First, check if the block is solid.
    if (maze->isSolid(pos.x, pos.y)) {
        // Get the screenspace coordinate of the block.
        ofPoint sPos = toScreenSpace(pos);


    } else {
        // Not solid, so we can't collide.
        result = false;
    }

    return result;
}

/*
 * Converts mazespace coordinates to screenspace.
 */
ofPoint Agent::toScreenSpace(ofPoint pos) {
    return ofPoint(((pos.x + 0.5)/mazeSize) * screenSize, ((pos.y + 0.5)/mazeSize) * screenSize);
}
