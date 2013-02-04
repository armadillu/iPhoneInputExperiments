/*
 *  box2.cpp
 *  iPhone Empty Example
 *
 *  Created by Oriol Ferrer Mesià on 19/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "box2.h"


box2::box2(){
	
	active = false;
	pmin.x = pmin.y = 0;
	size.x = size.y = 10;
	pmax = pmin + size;
	center = pmin + pmax * 0.5 ;
}


box2::box2( ofPoint origin, ofPoint size_ ){
	active = false;
	pmin = origin;
	size = size_;
	pmax = origin + size;
	center = pmin + pmax * 0.5 ;
}


bool box2::enableIfContains( ofPoint p){
	
	bool testResult = false;
	if ( 
		( p.x >= pmin.x && p.x <= pmax.x ) 
		&&
		( p.y >= pmin.y && p.y <= pmax.y ) 
		){
		
			testResult = true;
			active = true;
			lastPoint = p;
	}
	return testResult;
}

bool box2::contains( ofPoint p){
	
	if ( 
		( p.x >= pmin.x && p.x <= pmax.x ) 
		&&
		( p.y >= pmin.y && p.y <= pmax.y ) 
		){
		
			active = true;
			lastPoint = p;
		
	}else {
		active = false;
	}
	return active;
}


float box2::xAxis(){
	
	if ( active ){
		return ((lastPoint.x - pmin.x) / (size.x));
	}else 
		return 0.0f;
}

float box2::yAxis(){
	
	if ( active ){
		return ((lastPoint.y - pmin.y) / (size.y));
	}else 
		return 0.0f;
}


void box2::draw(){
	if (active)
		ofSetColor(255,0,0, 60);
	else
		ofSetColor(255,255,255, 60);
	ofRect(pmin.x, pmin.y, size.x, size.y);
	
	if (!active)
		return;
	
	ofSetColor(0xffffff	);
	ofRect(lastPoint.x, pmin.y, 1, size.y);
	ofRect(pmin.x, lastPoint.y, size.x, 1);
}