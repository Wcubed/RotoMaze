#include "WireframeCube.h"

// ---------- CONSTRUCTORS ----------

WireframeCube::WireframeCube(int _size)
{
    size = _size;

    // Set the mesh to only draw lines.
    cube.setMode(OF_PRIMITIVE_LINES);

    // ---- Make the vertices. ----

    for (int i = 0; i < 8; i++) {
        cube.addVertex(ofVec3f(vdata[i][0], vdata[i][1], vdata[i][2]));
    }

    // ---- Connect the vertices. ----

    for (int i = 0; i < 12; i++) {
        cube.addIndex(indices[i][0]);
        cube.addIndex(indices[i][1]);
    }

    // Allocate the framebuffer.
    gameScreen.allocate(1000, 1000, GL_RGBA);

    // ---- Create the plane. ----
    plane.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    // Create the vertices.
    plane.addVertex(ofVec3f(-1, -1, 0));
    plane.addVertex(ofVec3f(1, -1, 0));
    plane.addVertex(ofVec3f(1, 1, 0));
    plane.addVertex(ofVec3f(-1, 1, 0));

    // Set the texture coordinates to match that of the frame buffer.
    plane.addTexCoord(ofVec2f(0, 0));
    plane.addTexCoord(ofVec2f(gameScreen.getWidth(), 0));
    plane.addTexCoord(ofVec2f(gameScreen.getWidth(), gameScreen.getHeight()));
    plane.addTexCoord(ofVec2f(0, gameScreen.getHeight()));
}

/*
 * Draws the cube on the screen with the specified size.
 */

void WireframeCube::draw() {
    ofPushMatrix();

    ofTranslate(pos);
    ofRotateZ(xRot);

    // DEBUG (paralax)
    ofRotateX(ofGetMouseY()/100.0 - 5);
    ofRotateY(-(ofGetMouseX()/100.0 - 5));

    ofPushMatrix();
    ofScale(size*0.5, size*0.5, size*0.5);

    // Draw the wireframe.
    cube.draw();

    ofPopMatrix();

    // Draw the plane in the front part of the cube and slightly smaller.
    ofTranslate(0, 0, size*0.3);
    ofScale(size*0.5 - size*0.1, size*0.5 - size*0.1, size*0.5 - size*0.1);

    // Bind the framebuffer as a texture.
    gameScreen.getTexture().bind();

    // Draw the framebuffer on the plane.
    plane.draw();

    // Unbind the framebuffer.
    gameScreen.getTexture().unbind();

    ofPopMatrix();

}

// ---------- FRAMEBUFFER ----------

/*
 * Makes openframeworks draw to the framebuffer instead of to the screen.
 */
void WireframeCube::fboBegin() {
    gameScreen.begin();
}

/*
 * Resets openframeworks to draw to the screen.
 */
void WireframeCube::fboEnd() {
    gameScreen.end();
}

// ---------- SETTERS ---------

void WireframeCube::setPos(float x, float y, float z) {
    pos.set(x, y, z);
}

void WireframeCube::setSize(float _size) {
    size = _size;
}

void WireframeCube::setXRot(float angle) {
    xRot = angle;
}
