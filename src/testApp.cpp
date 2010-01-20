
#include "testApp.h"



//rotate -90, translate... to match horizontal iphone
ofPoint convertCoordinates(float x, float y){
	return ofPoint(y,x);
}

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(20, 20, 20);
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
	
	//this controls wheel (horizontal axis), so needs to be wide and not tall
	int areaW = 160;
	int areaH = 70;
	leftSensor = box2( ofPoint(0,0), ofPoint(areaW,areaH) );

	//this controls speed (vertical axis), so needs to be thin and tall
	areaW = 40;
	areaH = h;
	rightSensor = box2( ofPoint(w-areaW,0), ofPoint(areaW,areaH) );

	for (int i=0; i< MAX_TOUCHES; i++)
		touches[i] = NULL;
}


//--------------------------------------------------------------
void testApp::update(){

	if (leftSensor.isActive()){	//left sensor is direction
		float where = leftSensor.xAxis();
		where -= 0.5f;	//middle of sensor "neutral" zone. go straight. Press on either side to turn
		turn -= 5. * where;
	}

	if (rightSensor.isActive()){	//right sensor is speed
		float where = rightSensor.yAxis();
		where -= 0.2;		//20% above bottom is "neutral" zone. Go below to reverse, go above to go forward
		speed += 0.5 * where;
	}
	
	//update car
	car.x = car.x + speed * cos( DEG_TO_RAD * (turn+90) );
	car.y = car.y + speed * sin( DEG_TO_RAD * (turn+90) );	
	
	speed *= 0.95;
	
	//bounds
	if (car.y > h)
		car.y = 0;
	else
	if (car.y < 0)
		car.y = h;
	else
	if (car.x > w)
		car.x = 0;
	else
	if (car.x < 0)
		car.x = w;
}

	
//--------------------------------------------------------------
void testApp::draw(){
		
	//rotate world for iphone horizontal play
	setupProjection();
	glTranslatef(0, ofGetHeight(),0);
	glRotatef( -90  , 0,0,1);
	
	leftSensor.draw();
	rightSensor.draw();
	

	ofSetColor(0x777777);
	
	glPushMatrix();
		glTranslatef( car.x, car.y,0);
		glRotatef(turn, 0,0,1);
		int carW = 15;
		int carH = 35;

		ofRect( -carW * 0.5, -carH * 0.5, carW, carH);
	glPopMatrix();


	for (int i = 0; i< 3; i++){
		if ( touches[i] == NULL )
			ofSetColor(50,50,50);
		if ( touches[i] == &leftSensor )
			ofSetColor(0,255,0);
		if ( touches[i] == &rightSensor )
			ofSetColor(0,0,255);
		int ww = 30;
		ofRect(i*ww, h-ww, ww-2, ww-2);
	}

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

	if ( leftSensor.enableIfContains( t ) ){
		printf( "left active(%f,%f)\n", leftSensor.xAxis(), leftSensor.yAxis() );
		touches[touchId] = &leftSensor;
	}else {
		printf("no left\n");
	}

	if ( rightSensor.enableIfContains( t ) ){
		printf( "right active(%f,%f)\n", rightSensor.xAxis(), rightSensor.yAxis() );
		touches[touchId] = &rightSensor;
	}else {
		printf("no right\n");
	}
}


//--------------------------------------------------------------
void testApp::touchMoved(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	printf("touch %i moved at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
	
	if ( touches[touchId] != NULL){
		touches[touchId]->contains(t);
	}else {
		touchDown(x, y, touchId, data);
	}
}


//--------------------------------------------------------------
void testApp::touchUp(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	printf("touch %i up at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
	
	if ( touches[touchId] != NULL){
		touches[touchId]->reset();
		touches[touchId] = NULL;
	}
}


//--------------------------------------------------------------
void testApp::touchDoubleTap(float x, float y, int touchId, ofxMultiTouchCustomData *data){
	ofPoint t = convertCoordinates(x,y);
	//printf("touch %i double tap at (%i,%i)\n", touchId, (int)t.x, (int)t.y);
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

