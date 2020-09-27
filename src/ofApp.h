#pragma once

#include "ofMain.h"

class Rectangle {
public:
    //constructors---------s-------------------------------
    Rectangle();
    Rectangle(float, bool);
    
    //functions--------------------------------------------
    virtual void draw() {
        ofSetColor(color);      //set color of rectangle
        
        ofPushMatrix();         //push matrix stack, save current coordinate system
        ofTranslate(pos);       //translate coordinate system to default position vector
        ofRotateZDeg(deg);
        
        deg = deg + speed;         //increment deg based on speed & rotate
        if(deg > 360)  deg = speed;   //inline-if rotation reaches 359 deg, reset to initial deg
        ofDrawRectangle(-width/2, -height/2, width, height);    //adjust rectangle to origin
        ofPopMatrix();          //pop matrix stack, reset coordinate system
        
    }       //override draw
    
    virtual bool near(glm::vec3 p) {
        if(p.x <= pos.x + height && p.x >= pos.x - height &&
           p.y <= pos.y + height && p.y >= pos.y - height)
            return true;
        else
            return false;
    }     //override inside - check whether mouse is near rectangle
    
    //data-------------------------------------------------
    glm::vec3 pos;      //position vector of rectangle
    
    float width = 100;      //rectangle width
    float height = 200;    //...height
    float deg;          //degrees of rotation
    float speed = 1;         //speed of rotation specified in parameter
    ofColor color;      //color of rectangle
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    Rectangle r1, r1a, r1b, r2, r2a, r2b;      //rectangle calls
};
