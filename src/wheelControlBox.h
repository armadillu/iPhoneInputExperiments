/*
 *  wheelControlBox.h
 *  iPhoneCarInput
 *
 *  Created by Oriol Ferrer Mesià on 20/01/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "box2.h"

class wheelControlBox: public box2{

public:
	
	wheelControlBox() 
	: box2() {};
	
	wheelControlBox(ofPoint where, ofPoint size)
	: box2(where, size){};
	
	void draw();
};