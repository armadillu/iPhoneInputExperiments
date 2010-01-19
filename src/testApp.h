#pragma once

#include "ofMain.h"
#include "glu.h"
#include "ofxAccelerometer.h"
#include "ofxMultiTouch.h"
#include "box2.h"


class testApp : public ofSimpleApp, public ofxMultiTouchListener {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void setupProjection();
	void handleClick( ofPoint c );
	void resetClicks( ofPoint c );
	
	void keyPressed(int key) {}
	void keyReleased(int key)  {}
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void mouseReleased(int x, int y, int button );
	
	void touchDown(float x, float y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchMoved(float x, float y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchUp(float x, float y, int touchId, ofxMultiTouchCustomData *data = NULL);
	void touchDoubleTap(float x, float y, int touchId, ofxMultiTouchCustomData *data = NULL);
	
	int w, h;
	float turn;
	float speed;
	
	ofPoint	car;
	box2	turnLeft;
	box2	turnRight;
	
};

