#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(255, 255, 255);
    
    /*************************
     //SET BOUNDS
     *************************/
    //CREATE A RECTANGLE with ofPolyLine with multiple points on each side
    int numberofverticesperside=8;
    bounds.addVertex(ofPoint(0,0));
    bounds.bezierTo(ofPoint(0,ofGetHeight()/3), ofPoint(0,ofGetHeight()-(ofGetHeight()/3)), ofPoint(0,ofGetHeight()), numberofverticesperside);
    bounds.bezierTo(ofPoint(ofGetWidth()/3,ofGetHeight()), ofPoint(ofGetWidth()-(ofGetWidth()/3),ofGetHeight()), ofPoint(ofGetWidth(),ofGetHeight()), numberofverticesperside);
    bounds.bezierTo(ofPoint(ofGetWidth(),ofGetHeight()-(ofGetHeight()/3)), ofPoint(ofGetWidth(),ofGetHeight()/3), ofPoint(ofGetWidth(),0), numberofverticesperside);
    bounds.bezierTo(ofPoint(ofGetWidth()-(ofGetWidth()/3),0), ofPoint(ofGetWidth()/3,0), ofPoint(0,0), numberofverticesperside);
    
    //COPY THE VERTICES form ofPolyLine into ofMesh
    //We dot this te easily remove double vertices created by the bezierTo
    for (int i=0;i<bounds.size();++i) {
        polypoints.addVertex(ofVec3f(bounds[i].x,bounds[i].y,0));
    }
    polypoints.setMode(OF_PRIMITIVE_POINTS);
    //REMOVE DOUBLE VERTICES
    //POLY2TRI DOES NOT LIKE THAT
    polypoints.removeVertex(0);
    polypoints.removeVertex(numberofverticesperside-1);
    polypoints.removeVertex((numberofverticesperside-1)*2);
    polypoints.removeVertex((numberofverticesperside-1)*3);
    polypoints.removeVertex((numberofverticesperside-1)*4);
    
    
    /*************************
     //SET POINTS (in bounds)
     *************************/
    
    for (int i=0;i<200;++i) {
        ofPoint newpoint;
        newpoint.x = ofRandom(ofGetWidth());
        newpoint.y = ofRandom(ofGetHeight());
        points.push_back(newpoint);
    }
    
    
    /*************************
     //ADD HOLES
     *************************/
   
    ofPolyline line0;
    line0.addVertex(10,10);
    line0.addVertex(10,200);
    line0.addVertex(200,200);
    line0.addVertex(200,10);
    line0.close();
    ofPolyline line1;
    line1.addVertex(300,300);
    line1.addVertex(300,500);
    line1.addVertex(500,500);
    line1.addVertex(500,300);
    line1.close();
    holes.push_back(line0);
    holes.push_back(line1);
    
    
    triangulator.setSteinerPoints(points);
    triangulator.setHoles(holes);
    
    
    //DO TRIANGULATION
    triangulator.triangulate(polypoints);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    triangulator.triangulatedMesh.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    triangulator.triangulate(polypoints);
}