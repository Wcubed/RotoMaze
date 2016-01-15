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

    reset();

    running = true;
}

/*
 * Resets the game.
 */
void ofApp::reset() {
    // Clear out the agents.
    agents.clear();

    // Generate a new maze.
    maze = Maze();

    for (int i = 0; i < 3; i++) {
        int x, y;
        // Get a position that is not in a block.
        do {
            x = ofRandom(0, maze.size-1);
            y = ofRandom(0, maze.size-1);
        } while (maze.isSolid(x, y));

        // 1 player, the rest are enemies.
        if (i == 0) {
            player = Agent(&maze, ofPoint(x, x), wireCube.getFboWidth(), false);
        } else {
            agents.push_back(Agent(&maze, ofPoint(x, y), wireCube.getFboWidth(), true));
        }
    }

    win = false;
    lose = false;
    running = true;
}

//--------------------------------------------------------------
void ofApp::update(){

    // If the serial connection is ok.
    if (serial.isInitialized()) {

        // Update the serial and get the current value.
        serial.updateSerial();
        angle = serial.getAccelValue();
        //printf("Angle: %i", angle);
    } else {
        // Use mouse position for angle.
        //angle = 90;
        angle = ((float)mouseX / ofGetWidth() * 540) - 270;
    }

    // printf("Accelerometer Angle %i /n", angle);

    // Get the deltatime.
    double dt = ofGetLastFrameTime();
    //std::cout << 1 / dt << std::endl;

    // Update the cube and the maze with the angle.
    maze.setAngle(angle);
    wireCube.setZRot(angle);

    // Update the cube and the maze.
    maze.update();
    wireCube.update(dt);

    if (running) {
        // Update the agents.
        player.update(dt, angle);

        // Check if the player won.
        if (player.getMazePos() == maze.target) {
            running = false;
            win = true;
        }

        for (int i = 0; i < agents.size(); i++) {
            agents[i].update(dt, angle);

            // Check if the player lost.
            if (agents[i].getMazePos() == maze.target) {
                running = false;
                lose = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // ---------- Draw on framebuffer ----------

    ofEnableSmoothing();

    wireCube.fboBegin();

    ofBackground(0, 0, 0, 0);

    maze.draw(wireCube.getFboWidth());

    // Draw agents.
    for (int i = 0; i < agents.size(); i++) {
        agents[i].draw();
    }
    player.draw();

    wireCube.fboEnd();

    // ---------- Draw on actual window ----------
    ofBackground(0);

    if (win) {
        ofBackground(0, 100, 0);
    }
    if (lose) {
        ofBackground(100, 0, 0);
    }

    ofEnableSmoothing();

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

    // The cube.
    wireCube.draw();

    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Key debugging, only active when there is no accelerometer.
    if (!serial.isInitialized()) {
        if (key == 'a') {
            angle -= 1;
        }
        if (key == 'd') {
            angle += 1;
        }
    }

    if (key == 'r') {
        // r for reset.
        reset();
    }
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

