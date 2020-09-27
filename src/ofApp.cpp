#include "ofApp.h"


glm::vec3 dragPos, mouPos, diffPos;     //drag, mouse, and difference position vectors
bool dragSwitch1, dragSwitch2;        //bool switches for object drag

//constructor(default)------------------------------------------
Rectangle::Rectangle() {
    pos = glm::vec3(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0);     //set default position randomly within window
}

//constructor(position x, position y, speed of rotation)----------------
Rectangle::Rectangle(float s, bool h) {
    //set variables
    pos = glm::vec3(0, 0, 0);       //default 0
    speed = s;
    
    //width/height
    width = 20;
    height = (h) ? 50 : 100;    //denote height based on bool param. (1 = 50, 0 = 100)
    
    color = ofColor::blue;      //default blue
}



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    
    r1a = Rectangle(2, 0);        //set rect. to default 0 for translation
    r1b = Rectangle(5, 1);        //...
    
    r2.speed = 3;         //set to faster rotation for second rectangle
    r2a = Rectangle(7, 0);
    r2b = Rectangle(1, 1);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    //change colors based on drag switch
    r1.color = (dragSwitch1) ? ofColor::green : ofColor::orange;
    r2.color = (dragSwitch2) ? ofColor::green : ofColor::yellow;
    
    r1.draw();
    r2.draw();
    
    ofPushMatrix();
    ofTranslate(r1.pos);       //translate based on big rect. position
    ofRotateZDeg(r1.deg);    //rotate at same pace as big rect.
    r1a.pos.y = -r1.height/2;     //adjust rect. positions after translation
    r1b.pos.y = r1.height/2;
    r1a.draw();
    r1b.draw();
    ofPopMatrix();
    
    //repeat for rect 2
    ofPushMatrix();
    ofTranslate(r2.pos);
    ofRotateZDeg(r2.deg);
    r2a.pos.y = -r2.height/2;
    r2b.pos.y = r2.height/2;
    r2a.draw();
    r2b.draw();
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
    dragPos = glm::vec3(x, y, 0);
    if(dragSwitch1)
        r1.pos = dragPos - diffPos;
    if(dragSwitch2)
        r2.pos = dragPos - diffPos;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouPos = glm::vec3(x, y, 0);       //save mouse position on click
    if(r1.near(mouPos)) {
        diffPos = mouPos - r1.pos;      //if within bounds, calculate and save difference
        dragSwitch1 = true;      //flip drag switch on

    }
    else if(r2.near(mouPos)) {
        diffPos = mouPos - r2.pos;
        dragSwitch2 = true;
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    dragSwitch1 = false;         //turn off drag switch/default
    dragSwitch2 = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
