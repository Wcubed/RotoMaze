#include "WireframeCube.h"

// ---------- CONSTRUCTORS ----------

WireframeCube::WireframeCube(int _size)
{
    size = _size;

    mesh.setMode(OF_PRIMITIVE_LINES);

    // ---- Make the vertices. ----

    for (int i = 0; i < 8; i++) {
        mesh.addVertex(ofVec3f(vdata[i][0], vdata[i][1], vdata[i][2]));
    }

    // ---- Connect the vertices. ----

    for (int i = 0; i < 12; i++) {
        mesh.addIndex(indices[i][0]);
        mesh.addIndex(indices[i][1]);
    }
}

/*
 * Draws the cube on the screen with the specified size.
 */

void WireframeCube::draw() {
    ofPushMatrix();

    ofTranslate(pos);
    ofRotate(xRot);
    ofScale(size*0.5, size*0.5, size*0.5);

    mesh.draw();

    ofPopMatrix();
}

// --------- SETTERS ---------

void WireframeCube::setPos(float x, float y, float z) {
    pos.set(x, y, z);
}

void WireframeCube::setSize(float _size) {
    size = _size;
}

void WireframeCube::setXRot(float angle) {
    xRot = angle;
}
