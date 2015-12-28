#include "Maze.h"

Maze::Maze()
{
    // Create 40 random blocks.
    for (int i = 0; i < 40; i++) {
        maze[int(ofRandom(0, size))][int(ofRandom(0, size))] = true;
    }
}

void Maze::draw(int drawSize) {
    ofPushStyle();

    ofSetColor(255, 255, 255, 255);

    float blockSize = drawSize / size;

    // Draw the edges.
    ofSetLineWidth(4);

    ofDrawLine(0, 0, 0, drawSize);
    ofDrawLine(0, 0, drawSize, 0);
    ofDrawLine(drawSize, 0, drawSize, drawSize);
    ofDrawLine(0, drawSize, drawSize, drawSize);

    // Draw the blocks.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (maze[x][y]) {
                ofDrawRectangle(blockSize * x, blockSize * y, blockSize, blockSize);
            }
        }
    }

    ofPopStyle();
}
