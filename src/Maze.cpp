#include "Maze.h"

Maze::Maze()
{
    // Create all the blocks.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            blocks[x][y] = Block();
        }
    }

    // Make 50 random blocks solid.
    for (int i = 0; i < 50; i++) {
        blocks[int(ofRandom(0, size))][int(ofRandom(0, size))].solid = true;
    }
}

/*
 * Updates the maze.
 */
void Maze::update() {

    // Reset all blocks 'standable' variable.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            blocks[x][y].standable = false;
        }
    }

    // Go over every tile that is not a block.
    // and check whether you can stand in it without falling.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (!isSolid(x, y)) {

                if (angle >= 45 && angle <= 135) {
                    if (isSolid(x + 1, y)) {
                        blocks[x][y].standable = true;
                    }
                }

                if (angle >= -135 && angle <= -45) {
                    if (isSolid(x - 1, y)) {
                        blocks[x][y].standable = true;
                    }
                }

                if (angle >= -45 && angle <= 45) {
                    if (isSolid(x, y + 1)) {
                        blocks[x][y].standable = true;
                    }
                }

                if (angle <= -135 || angle >= 135) {
                    if (isSolid(x, y - 1)) {
                        blocks[x][y].standable = true;
                    }
                }

            }
        }
    }
}

/*
 * Draws the maze in a square with a side length of 'drawSize'.
 */
void Maze::draw(int drawSize) {
    ofPushStyle();

    float blockSize = drawSize / size;

    // Draw the blocks.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {

            if (isSolid(x, y)) {
                ofSetColor(255, 255, 255, 255);
                ofDrawRectangle(blockSize * x, blockSize * y, blockSize, blockSize);
            } else if (isStandable(x, y)) {
                ofSetColor(0, 255, 0, 150);
                ofDrawRectangle(blockSize * x, blockSize * y, blockSize, blockSize);
            }
        }
    }

    // Draw the edges.
    ofSetColor(255, 255, 255, 255);
    ofSetLineWidth(4);

    ofDrawLine(0, 0, 0, drawSize);
    ofDrawLine(0, 0, drawSize, 0);
    ofDrawLine(drawSize, 0, drawSize, drawSize);
    ofDrawLine(0, drawSize, drawSize, drawSize);

    ofPopStyle();
}

/*
 *
 */
void Maze::astarSearch() {

}

/*
 * Returns wether a certain position is solid.
 * If the position is out of range it is always solid.
 */
bool Maze::isSolid(int x, int y) {

    // If the position is within range.
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return blocks[x][y].solid;
    } else {
        return true;
    }
}

/*
 * Returns wether you can stand in a certain position.
 * If the position is out of range it is never standable.
 */
bool Maze::isStandable(int x, int y) {

    // If the position is within range.
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return blocks[x][y].standable;
    } else {
        return false;
    }
}
