#pragma once

#include "ofMain.h"
#include "ofxPoly2Tri.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		
    
        ofxPoly2Tri  triangulator;
    
        ofPolyline bounds;
        ofMesh  polypoints;
    
        vector<ofPoint> points;
        vector<ofPolyline>holes;
};
