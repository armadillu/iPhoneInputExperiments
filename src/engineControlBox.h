/*
 *  engineControlBox.h
 *  iPhoneCarInput
 *
 *  Created by Oriol Ferrer Mesià on 20/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "box2.h"

class engineControlBox: public box2{

public:
	
	engineControlBox() 
	: box2() {};
	
	engineControlBox(ofPoint where, ofPoint size)
	: box2(where, size){};
	
	void draw();
};