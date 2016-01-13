#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Setup the window.
    ofSetWindowShape(1000, 1000);

    // Set framerate to 60.
    ofSetFrameRate(60);

    // Initialize the wireframe cube.
    wireCube.setPos(0, 0, 100);
    wireCube.setSize(ofGetHeight()/2);
    wireCube.setZRot(10);

    serial.setup();

    agent = Agent(&maze, ofPoint(1, 1), wireCube.getFboWidth());
}

//--------------------------------------------------------------
void ofApp::update(){

    int angle;

    // If the serial connection is ok.
    if (serial.isInitialized()) {

        // Update the serial and get the current value.
        serial.updateSerial();
        angle = serial.getAccelValue();
    } else {
        // Use mouse position for angle.
        angle = ((float)mouseX / ofGetWidth() * 360) - 180;
    }

    // printf("Accelerometer Angle %i /n", angle);

    // Get the deltatime.
    double dt = ofGetLastFrameTime();

    // Update the cube and the maze with the angle.
    maze.setAngle(angle);
    wireCube.setZRot(angle);

    // Update the agents.
    agent.update(dt, angle);

    // Update the cube and the maze.
    maze.update();
    wireCube.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){

    // ---------- Draw on framebuffer ----------

    ofEnableSmoothing();

    wireCube.fboBegin();

    ofBackground(0, 0, 0, 0);

    maze.draw(wireCube.getFboWidth());

    // Draw agents.
    agent.draw();

    wireCube.fboEnd();

    // ---------- Draw on actual window ----------
    ofBackground(0);

    ofEnableSmoothing();

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    // The cube.
    wireCube.draw();



    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

    // Reposition and resize the wireframe cube.
    wireCube.setPos(0, 0, h/10);
    wireCube.setSize(h/2);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

