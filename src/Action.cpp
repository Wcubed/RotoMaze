#include "Action.h"

Action::Action()
{

}

/*
 * Creates a new Action with it's requirements.
 * The target does not have to be in the requirements list.
 */
Action::Action(ofPoint _target, vector<ActionReq> _reqs)
{
    target = _target;
    reqs = _reqs;

    reqs.push_back({_target, false});
}

/*
 * Returns the block an agent will be in after executing this action.
 *
 * origin: Point to test from.
 * gravAngle: Angle of gravity.
 * mirrored: Whether we are evaluating the mirrored version of this action.
 */
ofPoint Action::getAbsoluteTarget(ofPoint origin, float gravAngle, bool mirrored) {
    ofPoint absTarget = ofPoint(target);

    // If this is the mirrored version of the action:
    if (mirrored) {
        // Flip the x value.
        absTarget.x = -absTarget.x;
    }

    // Rotate the required position according to gravity.
    absTarget = ofVec2f(absTarget).getRotated(-gravAngle);

    // Round it to whole numbers.
    absTarget.x = round(absTarget.x);
    absTarget.y = round(absTarget.y);

    // Add the the origin to the test position to make it absolute.
    absTarget += origin;

    return absTarget;
}
