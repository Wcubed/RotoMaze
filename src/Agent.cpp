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
Agent::Agent(ofPoint _mazePos, int _mazeSize, int _screenSize)
{
    mazePos = ofPoint(0, 0);
    screenPos = ofPoint(0, 0);

    mazeSize = _mazeSize;
    screenSize = _screenSize;

    setMazePos(_mazePos);
}

/*
 * Updates the agent according to the angle of gravity.
 */
void Agent::update(double dt, float angle) {

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
    ofDrawCircle(0, 0, (screenSize / mazeSize)*0.5);

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
    screenPos.set(((mazePos.x + 0.5)/mazeSize) * screenSize, ((mazePos.y + 0.5)/mazeSize) * screenSize);
}
