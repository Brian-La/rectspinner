#include "ofApp.h"


//constructor(default)------------------------------------------
RectShape::RectShape(bool x) {
    pos = glm::vec3(ofRandom(ofGetWidth() / 2), ofRandom(ofGetHeight() / 2), 0);     //set default position randomly within window
    
    color = (x) ? ofColor::red : ofColor::blue;         //sys1 = red, sys2 = blue
}

//constructor(position x, position y, speed of rotation)----------------
RectShape::RectShape(float s, bool x) {
    //set variables
    pos = glm::vec3(0, 0, 0);       //default 0
    speed = s;
    
    //width/height
    width = (x) ? 50 : 100;
    height = 20;    //denote height based on bool param. (1 = 50, 0 = 100)
    
    color = ofColor::yellow;      //default yellow
}

//constructor(set width/height of each box primitive depending on )
Rects3D::Rects3D(RectShape a, RectShape a1, RectShape a2) {
    mainColor = a.color;
    aWidth = a.width;
    aHeight = a.height;
    
    outerColor = a1.color;
    a1Width = a1.width;
    a1Height = a1.height;
    a1speed = a1.speed;
    
    a2Width = a2.width;
    a2Height = a2.height;
    a2speed = a2.speed;
}

//node for system transformations
ofNode& Rects3D::getNode() {
    return b;
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(ofColor::black);
    
    //adjust r2 speed
    r2.speed = 2;
    
    //setup rect3D systems========================================================]]]
    sys1.setup();
    sys2.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    //change colors based on drag switch
    r1.color = (dragSwitch1) ? ofColor::green : ofColor::red;
    r2.color = (dragSwitch2) ? ofColor::green : ofColor::blue;
    
    //update deg rotations
    r1.update();
    r1a.update();
    r1b.update();
    
    r2.update();
    r2a.update();
    r2b.update();
    
    //update sys and positions========================================================]]]
    n1.setPosition(r1.pos.x, 0, r1.pos.y);      //node shift entire position
    n1.rotateDeg(-r1.speed, {0, 1, 0});      //rotate entire position based on speed
    sys1.update();
    
    n2.setPosition(r2.pos.x, 0, r2.pos.y);      //node shift entire position
    n2.rotateDeg(-r2.speed, {0, 1, 0});      //rotate entire position based on speed
    sys2.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(!camMode) {
        r1.draw();
        r2.draw();
        
        ofPushMatrix();
        ofTranslate(r1.pos);       //translate based on big rect. position
        ofRotateZDeg(r1.deg);    //rotate at same pace as big rect.
        r1a.pos.x = -r1.width/2;     //adjust rect. positions after translation
        r1b.pos.x = r1.width/2;
        r1a.draw();
        r1b.draw();
        ofPopMatrix();
        
        //repeat for rect 2
        ofPushMatrix();
        ofTranslate(r2.pos);
        ofRotateZDeg(r2.deg);
        r2a.pos.x = -r2.width/2;
        r2b.pos.x = r2.width/2;
        r2a.draw();
        r2b.draw();
        ofPopMatrix();
    }
    else {
        cam.begin();
        //sys draw=================================================================]]
        sys1.draw();
        sys2.draw();
        cam.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'm' || key == 'M') {
        camMode = !camMode;     //toggle camera
        
        if(camMode) {       //reset cam position if entering cam mode
            cam.setPosition ({ 500, 500, 1000 });
            cam.lookAt({500, 0, 500}, {0, 1, 0});
            cam.setFarClip(10000);
        }
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
    if(!camMode) {
        dragPos = glm::vec3(x, y, 0);
        if(dragSwitch1)
            r1.pos = dragPos - diffPos;
        if(dragSwitch2)
            r2.pos = dragPos - diffPos;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(!camMode) {
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
