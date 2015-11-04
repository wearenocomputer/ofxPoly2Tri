//
//  ofxPoly2Tri.h
//  poly2TriParticles
//
//  Created by Wim Vanhenden on 04/11/15.
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
    
    ofVboMesh vboMesh;
    
    bool       bUseVboMesh;
    
    ofPolyline currentline;
    
    float scalex;
    float scaley;
    
    
private:
    
    vector<ofPolyline> holes;
    vector<ofPoint>    steinerpoints;
    
    void doTriangulation(vector<p2t::Point*> bound);
    
    
    
};