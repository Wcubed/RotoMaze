#include "Maze.h"

Maze::Maze()
{
    // Create the actions.
    createActions();

    // Create all the blocks.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            blocks[x][y] = Block(x, y);
        }
    }

    // Make 50 random blocks solid.
    for (int i = 0; i < 50; i++) {
        blocks[int(ofRandom(0, size))][int(ofRandom(0, size))].solid = true;
    }

    // Randomly place the target on an empty spot.
    do {
        target.set(int(ofRandom(0, size)), int(ofRandom(0, size)));
    } while (isSolid(target.x, target.y));

    // Set all the blocks naive distance to the target.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            blocks[x][y].distToTarget = ofVec2f(x, y).distance(target);
        }
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

            for (BlockLink link : blocks[x][y].links) {
                ofSetColor(255, 255, 0);
                ofDrawLine((x+0.5) * blockSize, (y+0.5) * blockSize, (link.block->x+0.5) * blockSize, (link.block->y+0.5) * blockSize);
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

    // Draw reference point.
    ofSetColor(0, 0, 255);
    ofDrawCircle(-50, -50, 25);

    // Draw the target.
    ofSetColor(0, 255, 255, 150);
    ofDrawCircle((target.x + 0.5) * blockSize, (target.y + 0.5) * blockSize, blockSize);
    ofSetColor(0, 255, 255, 200);
    ofDrawCircle((target.x + 0.5) * blockSize, (target.y + 0.5) * blockSize, blockSize*0.5);
    ofSetColor(0, 255, 255, 220);
    ofDrawCircle((target.x + 0.5) * blockSize, (target.y + 0.5) * blockSize, blockSize*0.3);

    ofPopStyle();
}

/*
 *
 */
Block* Maze::astarSearch(int x, int y) {
    updatePaths(x, y);

    float shortestDist = ofVec2f(x, y).distance(target);
    Block* nextBlock = &blocks[x][y];

    for (BlockLink link : blocks[x][y].links) {
        Block* block = link.block;

        float targetDist = block->pos.distance(target);

        if (targetDist < shortestDist || shortestDist < 0) {
            shortestDist == targetDist;
            nextBlock = block;
        }
    }

    // Astar search.

    // Reset all the visited, marked, parent and link values.
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            blocks[x][y].visited = false;
            blocks[x][y].marked = false;
            blocks[x][y].parent = nullptr;
            blocks[x][y].links.clear();
        }
    }
    // Empty the queue and add the starting block.
    astarQueue.empty();
    astarQueue.push(&blocks[x][y]);

    bool done = false;

    while (!done) {

        // If queue is empty, end the search.
        if (astarQueue.empty()) {
            done = true;
            break;
        }

        // Get the most promising block in the list.
        Block* current = astarQueue.top();
        astarQueue.pop();

        // If the block is the target, end the search.
        if (current->pos == target) {
            done = true;
            break;
        }

        // See where we can go from this block.
        updatePaths(current->x, current->y);

        // Loop over all the possible links.
        for (BlockLink link : current->links) {
            // Calculate this blocks distance from the origin.
            float distFromOrigin = current->distFromOrigin + link.length;

            // Check if the block has already been visited.
            if (link.block->visited) {
                if (link.block->distFromOrigin <= distFromOrigin) {
                    // Nothing to do here: go to the next link.
                    continue;
                } else {
                    // We are going to update this node with new values.
                    // So we need to remove it from the queue first.
                    astarQueue.erase(link.block);
                }
            }

            // Set the blocks cost and the parent.
            link.block->distFromOrigin = distFromOrigin;
            link.block->parent = current;

            link.block->visited = true;

            // Add it to the queue.
            astarQueue.push(link.block);
        }

    }

    return nextBlock;
}

/*
 *
 */
void Maze::updatePaths(int x, int y) {

    Block* block = &blocks[x][y];

    // Clear the old data.
    block->links.clear();

    for (Action action : actions) {
        // Test for the unmirrored version.
        if (isActionFeasible(action, ofPoint(x, y), angle, false)) {
            BlockLink link;

            ofPoint targetPos = action.getAbsoluteTarget(ofPoint(x, y), angle, false);

            // Add the actions target to the links.
            link.block = &blocks[int(targetPos.x)][int(targetPos.y)];
            link.length = ofPoint(x, y).distance(link.block->pos);

            block->links.push_back(link);
        }

        // Test for mirrored version.
        if (isActionFeasible(action, ofPoint(x, y), angle, true)) {
            BlockLink link;

            ofPoint targetPos = action.getAbsoluteTarget(ofPoint(x, y), angle, true);

            // Add the actions target to the links.
            link.block = &blocks[int(targetPos.x)][int(targetPos.y)];
            link.length = ofPoint(x, y).distance(link.block->pos);

            block->links.push_back(link);
        }
    }
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

/*
 * Tests if an action is feasible.
 *
 * action: action to test.
 * origin: Point to test from.
 * gravAngle: Angle of gravity.
 * mirrored: Whether we are evaluating the mirrored version of this action.
 */
bool Maze::isActionFeasible(Action action, ofPoint origin, float gravAngle, bool mirrored) {
    bool feasible = true;

    for (ActionReq req : action.reqs) {
        ofPoint testPos = ofPoint(req.first);

        // If this is the mirrored version of the action:
        if (mirrored) {
            // Flip the x value.
            testPos.x = -testPos.x;
        }

        // Rotate the required position according to gravity.
        testPos = ofVec2f(testPos).getRotated(-gravAngle);

        // Round it to whole numbers.
        testPos.x = round(testPos.x);
        testPos.y = round(testPos.y);

        // Add the the origin to the test position to make it absolute.
        testPos += origin;

        // Check if the location in the maze is solid/not solid according to requirements.
        // If any requirement isn't true, this action isn't feasible.
        if (isSolid(testPos.x, testPos.y) != req.second) {
            feasible = false;
            break;
        }

        // If this location is the actions target, do an aditional check on whether we can actually stand there.
        if (testPos == action.getAbsoluteTarget(origin, gravAngle, mirrored)) {
            if (!isStandable(testPos.x, testPos.y)) {
                feasible = false;
                break;
            }
        }
    }

    return feasible;
}

/*
 * Initializes all possible actions.
 */
void Maze::createActions() {
    // 0T
    // XX
    Action act = Action(ofPoint(1, 0), vector<ActionReq>());
    act.reqs.push_back(ActionReq{ofPoint(1, 1), true});
    actions.push_back(act);

    // _T
    // 0X
    // X

    act = Action(ofPoint(1, -1), vector<ActionReq>());
    act.reqs.push_back(ActionReq{ofPoint(0, -1), false});
    act.reqs.push_back(ActionReq{ofPoint(1, 0), true});
    actions.push_back(act);

    // 0_
    // XT
    //  X

    act = Action(ofPoint(1, 1), vector<ActionReq>());
    act.reqs.push_back(ActionReq{ofPoint(1, 0), false});
    act.reqs.push_back(ActionReq{ofPoint(1, 2), true});
    actions.push_back(act);

    // __T
    // X_X
}
