#pragma once

#include "ofMain.h"

class RectShape {
public:
    //constructors-----------------------------------------
    RectShape(bool);
    RectShape(float, bool);
    
    //functions--------------------------------------------
    virtual void draw() {
        ofSetColor(color);      //set color of rectangle
        
        ofPushMatrix();         //push matrix stack, save current coordinate system
        ofTranslate(pos);       //translate coordinate system to default position vector
        ofRotateZDeg(deg);
        
        ofDrawRectangle(-width/2, -height/2, width, height);    //adjust rectangle to origin
        ofPopMatrix();          //pop matrix stack, reset coordinate system
        
    }       //override draw
    
    virtual void update() {
        deg += speed;         //increment deg based on speed & rotate
        if(deg > 360)  deg = speed;   //inline-if rotation reaches 359 deg, reset to initial deg
    }
    
    virtual bool near(glm::vec3 p) {
        if(p.x <= pos.x + height && p.x >= pos.x - height &&
           p.y <= pos.y + height && p.y >= pos.y - height)
            return true;
        else
            return false;
    }     //override inside - check whether mouse is near rectangle
    
    //data-------------------------------------------------
    glm::vec3 pos;      //position vector of rectangle
    
    float width = 200;      //rectangle width
    float height = 50;    //...height
    float deg = 0;          //degrees of rotation
    float speed = 1;         //speed of rotation specified in parameter
    ofColor color;      //color of rectangle
    
};


class Rects3D {
public:
    Rects3D(RectShape, RectShape, RectShape);    //constructor using 3 rectangles
    
    //functions---------------------------------------------
    void setup() {
        //material.setDiffuseColor(ofFloatColor::turquoise);      //set diffuse color
        
        //main box
        b.setWidth(aWidth);
        b.setHeight(aHeight);
        b.setDepth(depth);
        
        //outer boxes - affix transformations to main box
        b1.setParent(b);
        b1.setWidth(a1Width);
        b1.setHeight(a1Height);
        b1.setDepth(depth / 4.0);
        b1.move(-b.getWidth() / 2.0, b.getHeight() / 2.0, 0);       //affix boxes on main box
        
        b2.setParent(b);
        b2.setWidth(a2Width);
        b2.setHeight(a2Height);
        b2.setDepth(depth / 4.0);
        b2.move(b.getWidth() / 2.0, b.getHeight() / 2.0, 0);
    }
    void update() {
        //rotate outer boxes at a diff speed
        b1.rotateDeg(-a1speed, {0, 1, 0});
        b2.rotateDeg(-a2speed, {0, 1, 0});
    }
    void draw() {
        //material.begin();
        
        //draw boxes
        ofSetColor(mainColor);
        b.draw();
        ofSetColor(outerColor);
        b1.draw();
        b2.draw();

        //material.end();
    }
    ofNode& getNode();          //return node of system
    
    ofBoxPrimitive b, b1, b2;       //box primitives
    ofMaterial material;        //keep material color
    
    float aWidth, aHeight, a1Width, a1Height, a2Width, a2Height;       //height/width
    float a1speed = 0;           //speed of rotation for smaller boxes
    float a2speed = 0;
    float depth = 100;        //depth of boxes
    
    ofColor mainColor, outerColor;
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
		
    glm::vec3 dragPos, mouPos, diffPos;     //drag, mouse, and difference position vectors
    bool dragSwitch1, dragSwitch2, camMode;        //bool switches for object drag, camera mode toggle
    
    RectShape r1 = RectShape(true);
    RectShape r2 = RectShape(false);
    RectShape r1a = RectShape(2, 0);
    RectShape r1b = RectShape(5, 1);
    RectShape r2a = RectShape(7, 0);
    RectShape r2b = RectShape(1, 1);      //rectangle calls
    
    Rects3D sys1 = Rects3D(r1, r1a, r2b);
    Rects3D sys2 = Rects3D(r2, r2a, r2b);
    
    ofNode& n1 = sys1.getNode();
    ofNode& n2 = sys2.getNode();
    
    ofEasyCam cam;
};
