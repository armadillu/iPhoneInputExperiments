/*
 *  engineControlBox.cpp
 *  iPhoneCarInput
 *
 *  Created by Oriol Ferrer Mesià on 20/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "engineControlBox.h"

void engineControlBox::draw(){

	if (!active){
		ofSetColor(255,255,255);
		ofRect(pmin.x, pmin.y, size.x, size.y);
	}else{

		float y = yAxis();
		if ( y > 0.2)
			ofSetColor( 0, (y-0.2) * (1./0.8) * 255 ,0);
		else
			ofSetColor( (1-((y * 5.))) * 255, 0 ,0);
		
		ofRect(pmin.x, pmin.y, size.x, size.y);
		
		//gas line
		ofSetColor(0xffffff);
		ofRect(pmin.x, lastPoint.y -2, size.x, 4);

	}
}
