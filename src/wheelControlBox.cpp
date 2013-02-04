/*
 *  engineControlBox.cpp
 *  iPhoneCarInput
 *
 *  Created by Oriol Ferrer Mesià on 20/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "wheelControlBox.h"

void wheelControlBox::draw(){

	if (!active){
		ofSetColor(255,255,255);
		ofRect(pmin.x, pmin.y, size.x, size.y);
	}else{

		float x = xAxis();
		x -= 0.5;
		x = fabs(x);
		x *= 2.;
		
		x*= 200;
		
		ofSetColor(0,x,x);
		ofRect(pmin.x, pmin.y, size.x, size.y);
		
		//gas line
		ofSetColor(0xffffff);
		ofRect(lastPoint.x-2, pmin.y, 4, size.y);

	}
}
