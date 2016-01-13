#ifndef OFEDGEBOXPRIMITIVE_H
#define OFEDGEBOXPRIMITIVE_H

#include "ofMain.h"

/*
 * A cube consisting only of edges.
 * It has a framebuffer which will be drawn inside the cube.
 */
class WireframeCube
{
public:
    WireframeCube() : WireframeCube(100) {}
    WireframeCube(int _size);

    void update(float dt);
    void draw();

    void fboBegin();
    void fboEnd();

    int getFboWidth();
    int getFboHeight();

    void setPos(float x, float y, float z);
    void setSize(float _size);
    void setZRot(float angle);

private:

    // Points of the cube.
    const GLfloat vdata[8][3] = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
        {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1},
    };

    // Lines between the points.
    const GLint indices[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Border around the drawing area, so that particles that go off of it can still be drawn.
    int borderSize = 100;

    // Position, scaling and rotation.
    ofVec3f pos;
    float size;
    float xRot;
    float yRot;
    float zRot;

    // Rotation directions (the cube 'floats' along the X and Y rotation axis).
    bool xRotDir;
    bool yRotDir;

    // Mesh data for the cube.
    ofMesh cube;
    // Mesh data for the framebuffer plane.
    ofMesh plane;

    // Framebuffer which will be drawn on a plane inside the cube.
    ofFbo gameScreen;
};

#endif // OFEDGEBOXPRIMITIVE_H
