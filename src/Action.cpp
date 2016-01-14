#include "Action.h"

Action::Action()
{

}

/*
 * Creates a new Action with it's requirements.
 * The target does not have to be in the requirements list.
 */
Action::Action(ofPoint _target, ofVec2f vel, vector<ActionReq> _reqs)
{
    target = _target;
    reqs = _reqs;
    neededVel = vel;

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

    // Compensate for the angle of gravity (rotate the other way).
    absTarget = ofVec2f(absTarget).getRotated(-gravAngle);

    // Round it to whole numbers.
    absTarget.x = round(absTarget.x);
    absTarget.y = round(absTarget.y);

    // Add the the origin to the test position to make it absolute.
    absTarget += origin;

    return absTarget;
}

/*
 * Returns the needed velocity according to the angle of gravity and whether the action is mirrored.
 */
ofVec2f Action::getNeededVel(float gravAngle, bool mirrored) {
    ofVec2f vel = neededVel;

    // If this is the mirrored version of the action:
    if (mirrored) {
        // Flip the x value.
        vel.x = -vel.x;
    }

    // Compensate for the angle of gravity (rotate the other way)
    vel.rotate(-gravAngle);

    return vel;
}
