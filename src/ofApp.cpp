#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // Setup the window.
    ofSetWindowShape(1000, 1000);

    wireCube.setPos(0, 0, 100);
    wireCube.setSize(ofGetHeight()/2);
    wireCube.setXRot(100);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableSmoothing();

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);

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
    wireCube.setSize(h/2);
    wireCube.setPos(0, 0, h/10);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

