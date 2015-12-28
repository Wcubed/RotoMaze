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
    gameScreen.allocate(500, 500, GL_RGBA);

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
 * Updates the cube.
 * It will slowly spin within 10 degrees along the X and Y axis.
 */
void WireframeCube::update(float dt) {

    // We rotate between +2 and -2 degrees.
    if (xRot > 3) {
        xRotDir = false;
    } else if (xRot < -3) {
        xRotDir = true;
    }

    if (yRot > 3) {
        yRotDir = false;
    } else if (yRot < -3) {
        yRotDir = true;
    }

    // Rotate along the X axis.
    if (xRotDir) {
        xRot += 0.7 * dt;
    } else {
        xRot -= 0.7 * dt;
    }

    // Rotate along the Y axis.
    if (yRotDir) {
        yRot += 0.4 * dt;
    } else {
        yRot -= 0.4 * dt;
    }
}

/*
 * Draws the cube on the screen with the specified size.
 */
void WireframeCube::draw() {
    ofPushMatrix();
    ofPushStyle();

    ofTranslate(pos);
    ofRotateZ(zRot);

    // DEBUG (paralax)
    ofRotateX(xRot);
    ofRotateY(yRot);

    ofPushMatrix();
    ofScale(size*0.5, size*0.5, size*0.5);

    // Draw the wireframe.
    ofSetColor(0, 150, 0);
    cube.draw();

    ofPopMatrix();

    // Draw the plane in the front part of the cube and slightly smaller.
    ofSetColor(255);
    ofTranslate(0, 0, size*0.3);
    ofScale(size*0.5 - size*0.1, size*0.5 - size*0.1, size*0.5 - size*0.1);

    // Bind the framebuffer as a texture.
    gameScreen.getTexture().bind();

    // Draw the framebuffer on the plane.
    plane.draw();

    // Unbind the framebuffer.
    gameScreen.getTexture().unbind();

    ofPopStyle();
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

/*
 * Returns the height of the framebuffer.
 */
int WireframeCube::getFboHeight() {
    return gameScreen.getHeight();
}

/*
 * Returns the width of the framebuffer.
 */
int WireframeCube::getFboWidth() {
    return gameScreen.getWidth();
}

// ---------- SETTERS ---------

void WireframeCube::setPos(float x, float y, float z) {
    pos.set(x, y, z);
}

void WireframeCube::setSize(float _size) {
    size = _size;
}

void WireframeCube::setZRot(float angle) {
    zRot = angle;
}
