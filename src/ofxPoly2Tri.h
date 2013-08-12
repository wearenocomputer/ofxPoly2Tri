//
//  ofxPoly2Tri.h
//  poly2TriParticles
//
//  Created by Wim Vanhenden on 12/08/13.
//
//

#pragma once
#include "ofMain.h"
#include "poly2tri.h"

using namespace p2t;

class ofxPoly2Tri {
  
public:
    
    
    void setHoles(vector<ofPolyline> incholes);
    void setSteinerPoints(vector<ofPoint> incpoints);
    void triangulate(ofPolyline bounds);
    void triangulate(ofMesh bounds);
    
    ofMesh triangulatedMesh;
    
    
private:
    
    vector<ofPolyline> holes;
    vector<ofPoint>    steinerpoints;
    
    void doTriangulation(vector<p2t::Point*> bound);
    
};