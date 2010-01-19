/*
 *  2Dbox.h
 *  iPhone Empty Example
 *
 *  Created by Oriol Ferrer Mesià on 19/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#ifndef _BOX2_INC
#define _BOX2_INC

#include "ofMain.h"

class box2{
	
	public:
	
		box2();
		box2( ofPoint origin, ofPoint size );
		~box2(){};

		bool enableIfContains(ofPoint);	//call contains first
		float xAxis();			//then you can query where the hit was % wise
		float yAxis();
		void disableIfContains(ofPoint);	//call contains first

		void reset(){active=false;}
		void draw();
	
		bool isActive(){return active;}
		void setActive(){active = true;}

		ofPoint pmin, pmax, center;
		ofPoint size;
	
		bool active;
		ofPoint	lastPoint;
};

#endif
