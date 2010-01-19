
#include "testApp.h"



//rotate -90, translate... to match horizontal iphone
ofPoint convertCoordinates(float x, float y){
	return ofPoint(y,x);
}

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(50, 50, 50);
	ofSetBackgroundAuto(true);
	glEnableClientState( GL_VERTEX_ARRAY );  // this should be in OF somewhere.  
	ofSetFrameRate(60);
	ofEnableSmoothing();
	
	// initialize the accelerometer
	//ofxAccelerometer.setup();
	
	// touch events will be sent to myTouchListener
	ofxMultiTouch.addListener(this);
	
	turn = 0;
	speed = 0;
	
	w = ofGetHeight();
	h = ofGetWidth();
	
	car.x = w * 0.5;
	car.y = h * 0.2;
	
	ofDisableSetupScreen();
	setupProjection();
	
	turnLeft = box2( ofPoint(0,0), ofPoint(150,200) );
	turnRight = box2( ofPoint(w-150,0), ofPoint(150,200) );
}


//--------------------------------------------------------------
void testApp::update(){

	if (turnLeft.isActive()){
		turn += 1.0;
		speed += turnLeft.yAxis();
	}

	if (turnRight.isActive()){
		turn -= 1.0;
		speed += turnRight.yAxis();
	}
	
	//update car
	car.x = car.x + speed * cos( DEG_TO_RAD * (turn+90) );
	car.y = car.y + speed * sin( DEG_TO_RAD * (turn+90) );	
	
	speed *= 0.95;
	
	if (car.y > h)
		car.y = 0;
}

	
//--------------------------------------------------------------
void testApp::draw(){
		
	//rotate world for iphone horizontal play
	setupProjection();
	glTranslatef(0, ofGetHeight(),0);
	glRotatef( -90  , 0,0,1);
	
	turnLeft.draw();
	turnRight.draw();

	ofSetColor(0x777777);
	
	glPushMatrix();
		glTranslatef( car.x, car.y,0);
		glRotatef(turn, 0,0,1);
		int carW = 30;
		int carH = 70;

		ofRect( -carW * 0.5, -carH * 0.5, carW, carH);
	glPopMatrix();
	
	ofRect(0,0, 5,5);
}


void testApp::exit() {
	printf("exit()\n");
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	// this will never get called 	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
//	printf("frameRate: %.3f, frameNum: %i\n", ofGetFrameRate(), ofGetFrameNum());
//	ofDisableSmoothing();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::touchDown(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	printf("touch %i down at (%d,%d)\n", touchId, (int)t.x, (int)t.y);
	handleClick(t);
}

//--------------------------------------------------------------
void testApp::touchMoved(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	printf("touch %i moved at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
	handleClick(t);
}

//--------------------------------------------------------------
void testApp::touchUp(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	printf("touch %i up at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
	//handleClick(t);
	resetClicks(t);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	//printf("touch %i double tap at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
	handleClick(t);
}

void testApp::resetClicks(ofPoint c){
	turnLeft.disableIfContains(c);
	turnRight.disableIfContains(c);
}


void testApp::handleClick( ofPoint c ){

	if ( turnLeft.enableIfContains( c ) ){
		printf( "left active(%f,%f)\n", turnLeft.xAxis(), turnLeft.yAxis() );
	}

	if ( turnRight.enableIfContains( c ) ){
		printf( "right active(%f,%f)\n", turnRight.xAxis(), turnRight.yAxis() );
	}
}

void testApp::setupProjection(){

	int w = ofGetWidth();
	int h = ofGetHeight();

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)w / 2.0;
	float eyeY 		= (float)h / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);
}

