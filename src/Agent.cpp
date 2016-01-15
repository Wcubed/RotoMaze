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
Agent::Agent(Maze* _maze, ofPoint _mazePos, int _screenSize, bool enemy)
{
    maze = _maze;

    isEnemy = enemy;

    mazePos = ofPoint(0, 0);
    screenPos = ofPoint(0, 0);

    mazeSize = maze->getSize();
    screenSize = _screenSize;

    blockSize = screenSize / mazeSize;
    halfBSize = blockSize*0.5;
    radius = blockSize*0.4;

    maxSpeed = radius*10;

    setMazePos(_mazePos);
}

/*
 * Updates the agent according to the angle of gravity.
 */
void Agent::update(double dt, float gravAngle) {

    // Calculate the acceleration due to gravity.
    // A block is two meters high. On this scale falling looks good.
    ofVec2f acc = ofVec2f(0, 9.81 * halfBSize);
    acc.rotate(-gravAngle);
    acc = acc * dt;

    // Update the new velocity.
    vel += acc;

    // Update the location with the speed.
    ofPoint newPos = ofPoint(screenPos);
    newPos += vel * dt;

    ofPoint noCollPos = ofPoint(screenPos);

    horCol = false;
    verCol = false;
    corCol = false;

    // Make sure this new location doesn't collide with anything.
    for (int x = mazePos.x -1; x <= mazePos.x +1; x++) {
        for (int y = mazePos.y -1; y <= mazePos.y +1; y++) {
            if (collidesWithBlock(newPos, ofPoint(x, y))) {
                // Collision! Change the velocity accordingly.

                // Screenspace position of the block we have a collision with.
                ofPoint blockPos = toScreenSpace(ofPoint(x, y));

                if (newPos.x <= blockPos.x + halfBSize && newPos.x >= blockPos.x - halfBSize) {
                    // "Vertical" collision.
                    // If we are moving in the direction of the block: stop the y movement.
                    if (ofSign(blockPos.y - newPos.y) == ofSign(vel.y)) {
                        vel.y = 0;
                    }

                    verCol = true;

                    // Get a position that we know is not inside the block.
                    if (newPos.y < blockPos.y) {
                        noCollPos.y = blockPos.y - halfBSize - radius;
                    } else {
                        noCollPos.y = blockPos.y + halfBSize + radius;
                    }

                } else if (newPos.y <= blockPos.y + halfBSize && newPos.y >= blockPos.y - halfBSize) {
                    // "Horizontal" collision.
                    // If we are moving in the direction of the block: stop the x movement.
                    if (ofSign(blockPos.x - newPos.x) == ofSign(vel.x)) {
                        vel.x = 0;
                    }

                    horCol = true;

                    // Get a position that we know is not inside the block.
                    if (newPos.x < blockPos.x) {
                        noCollPos.x = blockPos.x - halfBSize - radius;
                    } else {
                        noCollPos.x = blockPos.x + halfBSize + radius;
                    }
                } else {
                    // Corner collision.

                    // Check if we do not already have a horizontal or vertical collision.

                    if (!(horCol || verCol)) {

                        corCol = true;

                        // Get the distance from the block center.
                        ofVec2f dist = newPos - blockPos;

                        if (dist.x < 0) {
                            dist.x = -dist.x;
                        }
                        if (dist.y < 0) {
                            dist.y = -dist.y;
                        }

                        // Get the distance (and the angle of attack) from the corner.
                        ofVec2f cornerDist = ofVec2f(dist.x - halfBSize, dist.y - halfBSize);

                        if (cornerDist.x > cornerDist.y) {
                            // "Horizontal" collision.
                            // If we are moving in the direction of the block: stop the x movement.
                            if (ofSign(blockPos.x - newPos.x) == ofSign(vel.x)) {
                                vel.x = 0;
                            }
                        } else {
                            // "Vertical" collision.
                            // If we are moving in the direction of the block: stop the y movement.
                            if (ofSign(blockPos.y - newPos.y) == ofSign(vel.y)) {
                                vel.y = 0;
                            }
                        }

                        // Mega hacky way to prevent the agents from getting stuck in a corner.
                        /*if (newPos.x > blockPos.x && newPos.y > blockPos.y) {
                            noCollPos.x = blockPos.x + (halfBSize + radius);
                            noCollPos.y = blockPos.y + (halfBSize + radius);
                        } else if (newPos.x > blockPos.x && newPos.y < blockPos.y) {
                            noCollPos.x = blockPos.x + (halfBSize + radius);
                            noCollPos.y = blockPos.y - (halfBSize + radius);
                        } else if (newPos.x < blockPos.x && newPos.y > blockPos.y) {
                            noCollPos.x = blockPos.x - (halfBSize + radius);
                            noCollPos.y = blockPos.y + (halfBSize + radius);
                        } else if (newPos.x < blockPos.x && newPos.y < blockPos.y) {
                            noCollPos.x = blockPos.x - (halfBSize + radius);
                            noCollPos.y = blockPos.y - (halfBSize + radius);
                        }*/
                    }
                }

                // Get the distance from the block center.
                ofVec2f dist = newPos - blockPos;

                // Take only the distance perpendicular to the edge we are currently standing on.
                if (dist.x * dist.x > dist.y * dist.y) {
                    dist.y = 0;
                } else {
                    dist.x = 0;
                    dist.y = -dist.y;
                }

                ofVec2f gravVec = ofVec2f(0, 1);
                gravVec.rotate(gravAngle);

                float alpha = dist.angle(gravVec);

                // Do we have traction here?
                if (alpha < 45 && alpha > -45) {
                    vel.set(1, 0);

                    // Search for the next best block and get the required velocity.
                    ofVec2f neededVel = maze->astarSearch(mazePos.x, mazePos.y);

                    // Scale the velocity according to the block size.
                    vel = neededVel * blockSize;
                }
            }
        }
    }

    // Calculate the new position again.
    // But this time with a velocity vector that won't place us inside a wall.
    newPos = ofPoint(noCollPos);
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

    ofFill();

    // Draw the body.
    if (isEnemy) {
        ofSetColor(200, 0, 0);
    } else {
        ofSetColor(0, 200, 0);
    }
    ofDrawCircle(0, 0, radius);

    // Draw the eye.
    ofSetColor(255);
    ofDrawCircle(0, 0, radius*0.7);

    // Draw the pupil.
    ofPushMatrix();
    ofRotate(-vel.angle(ofVec2f(1, 0)));
    ofSetColor(0);

    ofDrawCircle(radius*0.3, 0, radius*0.3);
    ofPopMatrix();

    // Draws collision modes when debug is enabled.
    if (debug) {
        if (horCol) {
            ofSetColor(0, 200, 0);
            ofDrawRectangle(-radius*0.5, -radius*0.2, radius, radius*0.4);
        }
        if (verCol) {
            ofSetColor(0, 0, 200);
            ofDrawRectangle(-radius*0.2, -radius*0.5, radius*0.4, radius);
        }
        if (corCol) {
            ofSetColor(0, 200, 200);
            ofDrawCircle(0, 0, radius*0.4);
        }
    }

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
    mazePos.set(int((screenPos.x / screenSize) * mazeSize), int((screenPos.y / screenSize) * mazeSize));
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
bool Agent::collidesWithBlock(ofPoint myScreenPos, ofPoint blockmazePos) {
    bool result = false;

    // First, check if the block is solid.
    if (maze->isSolid(blockmazePos.x, blockmazePos.y)) {
        // Get the screenspace coordinate of the block.
        ofPoint sBlockPos = toScreenSpace(blockmazePos);

        // Get the distance between the agent and the block.
        ofVec2f dist = myScreenPos - sBlockPos;

        if (dist.x < 0) {
            dist.x = -dist.x;
        }
        if (dist.y < 0) {
            dist.y = -dist.y;
        }

        // Check for collision.
        if ((dist.x < radius + halfBSize && dist.y < halfBSize) || // Left and right.
            (dist.y < radius + halfBSize && dist.x < halfBSize) || // Up and down.
            (ofDist(0, 0, dist.x - halfBSize, dist.y - halfBSize) < radius)) // Corners.
        {
            result = true;
        }
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

/*
 * Converts screenspace coordinates to mazespace.
 */
ofPoint Agent::toMazeSpace(ofPoint pos) {
    return ofPoint(int((pos.x / screenSize) * mazeSize), int((pos.y / screenSize) * mazeSize));
}
