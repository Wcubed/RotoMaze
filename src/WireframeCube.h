#ifndef OFEDGEBOXPRIMITIVE_H
#define OFEDGEBOXPRIMITIVE_H

#include "ofMain.h"

/*
 * A cube consisting only of edges.
 */
class WireframeCube
{
public:
    WireframeCube() : WireframeCube(100) {}
    WireframeCube(int _size);

    void draw();

    void setPos(float x, float y, float z);
    void setSize(float _size);
    void setXRot(float angle);

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

    // Position, scaling and rotation.
    ofVec3f pos;
    float size;
    float xRot;

    // The actual mesh data.
    ofMesh mesh;
};

#endif // OFEDGEBOXPRIMITIVE_H
