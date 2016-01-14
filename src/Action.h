#ifndef ACTION_H
#define ACTION_H

#include "ofMain.h"

typedef pair<ofPoint, bool> ActionReq;

/*
 * Defines a possible action that can be executed by the agent.
 */
class Action
{
public:
    Action();
    Action(ofPoint _target, ofVec2f vel, vector<ActionReq> _reqs);

    ofPoint getAbsoluteTarget(ofPoint origin, float gravAngle, bool mirrored);
    ofVec2f getNeededVel(float gravAngle, bool mirrored);

public:

    vector<ActionReq> reqs; // Which blocks have to be solid or empty for this action.

private:

    ofPoint target; // Where the agent will end up when he executes this action.

    // Velocity needed to have a high chance of succesfully executing this action.
    // To convert this to screenspace it has to be multiplied by the block size.
    ofVec2f neededVel;
};

#endif // ACTION_H
