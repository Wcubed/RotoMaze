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
    Action(ofPoint _target, vector<ActionReq> _reqs);

    ofPoint getAbsoluteTarget(ofPoint origin, float gravAngle, bool mirrored);

    ofPoint target; // Where the agent will end up when he executes this action.

    vector<ActionReq> reqs; // Which blocks have to be solid or empty for this action.
};

#endif // ACTION_H
