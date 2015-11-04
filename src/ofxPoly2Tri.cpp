//
//  ofxPoly2Tri.cpp
//  poly2TriParticles
//
//  Created by Wim Vanhenden on 04/11/15.
//
//

#include "ofxPoly2Tri.h"


void ofxPoly2Tri::setHoles(vector<ofPolyline> incholes) {
    holes.clear();
    holes = incholes;
}

void ofxPoly2Tri::setSteinerPoints(vector<ofPoint> incpoints) {
    steinerpoints.clear();
    steinerpoints = incpoints;
}

void ofxPoly2Tri::triangulate(ofPolyline bounds) {
    
    vector<p2t::Point*> bound;
    vector<ofPoint>edgepoints = bounds.getVertices();
    for (int i=0;i<edgepoints.size();++i) {
        bound.push_back(new p2t::Point(edgepoints[i].x,edgepoints[i].y));
    }
    doTriangulation(bound);
}

void ofxPoly2Tri::triangulate(ofMesh bounds) {
    vector<p2t::Point*> bound;
    vector<ofPoint>edgepoints = bounds.getVertices();
    for (int i=0;i<edgepoints.size();++i) {
        bound.push_back(new p2t::Point(edgepoints[i].x,edgepoints[i].y));
    }
    doTriangulation(bound);
}


/***************************
 **** PRIVATE METHODS *******
 ***************************/

void ofxPoly2Tri::doTriangulation(vector<p2t::Point*> bound) {
    CDT *cdt = new CDT(bound);
    
    if (steinerpoints.size()>0) {
        //ADD POINTS
        for (int i=0;i<steinerpoints.size();++i) {
            p2t::Point *point = new p2t::Point(steinerpoints[i].x,steinerpoints[i].y);
            cdt->AddPoint(point);
        }
    }
    
    if (holes.size()>0) {
        //ADD HOLES
        for (int i=0;i<holes.size();++i) {
            vector<p2t::Point*> hole;
            vector<ofPoint>holepoints = holes[i].getVertices();
            for (int i=0;i<holepoints.size();++i) {
                p2t::Point *p = new p2t::Point();
                p->set(holepoints[i].x, holepoints[i].y);
                hole.push_back(p);
            }
            cdt->AddHole(hole);
        }
    }
    
    cdt->Triangulate();
    
    if (bUseVboMesh) {
        
        vboMesh.clear();
        
        vboMesh.setUsage(GL_DYNAMIC_DRAW);
        vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        for (int i = 0; i < cdt->GetTriangles().size(); i++){
            p2t::Triangle *ortriangle = cdt->GetTriangles()[i];
            
            if (ortriangle->IsInterior()) {
                vboMesh.addVertex(ofVec3f(ortriangle->GetPoint(0)->x,ortriangle->GetPoint(0)->y,0));
                vboMesh.addVertex(ofVec3f(ortriangle->GetPoint(1)->x,ortriangle->GetPoint(1)->y,0));
                vboMesh.addVertex(ofVec3f(ortriangle->GetPoint(2)->x,ortriangle->GetPoint(2)->y,0));
                
                float val =ofRandom(220,255);
                
                vboMesh.addColor(ofColor(val,val,val));
                vboMesh.addColor(ofColor(val,val,val));
                vboMesh.addColor(ofColor(val,val,val));
                
                vboMesh.addNormal(ofVec3f(0,0,1));
                vboMesh.addNormal(ofVec3f(0,0,1));
                vboMesh.addNormal(ofVec3f(0,0,1));
                
                float xval = ((ortriangle->GetPoint(0)->x+scalex)/(scalex*2))*512;
                float yval = ((ortriangle->GetPoint(0)->y+scaley)/(scaley*2))*512;
                
                float xvala = ((ortriangle->GetPoint(1)->x+scalex)/(scalex*2))*512;
                float yvala = ((ortriangle->GetPoint(1)->y+scaley)/(scaley*2))*512;
                
                float xvalb = ((ortriangle->GetPoint(2)->x+scalex)/(scalex*2))*512;
                float yvalb = ((ortriangle->GetPoint(2)->y+scaley)/(scaley*2))*512;
                
                vboMesh.addTexCoord(ofVec2f(xval,yval));
                vboMesh.addTexCoord(ofVec2f(xvala,yvala));
                vboMesh.addTexCoord(ofVec2f(xvalb,yvalb));
                
            }
        }
        
    } else {
        
        triangulatedMesh.clear();
        
        triangulatedMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        
        for (int i = 0; i < cdt->GetTriangles().size(); i++){
            p2t::Triangle *ortriangle = cdt->GetTriangles()[i];
            
            if (ortriangle->IsInterior()) {
                
                //ofColor randomColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
                triangulatedMesh.addVertex(ofVec3f(ortriangle->GetPoint(0)->x,ortriangle->GetPoint(0)->y));
                triangulatedMesh.addVertex(ofVec3f(ortriangle->GetPoint(1)->x,ortriangle->GetPoint(1)->y));
                triangulatedMesh.addVertex(ofVec3f(ortriangle->GetPoint(2)->x,ortriangle->GetPoint(2)->y));
                float val =ofRandom(220,255);
                
                triangulatedMesh.addColor(ofColor(val,val,val));
                triangulatedMesh.addColor(ofColor(val,val,val));
                triangulatedMesh.addColor(ofColor(val,val,val));
                
                triangulatedMesh.addNormal(ofVec3f(0,0,1));
                triangulatedMesh.addNormal(ofVec3f(0,0,1));
                triangulatedMesh.addNormal(ofVec3f(0,0,1));
                
                float xval = ((ortriangle->GetPoint(0)->x+scalex)/(scalex*2))*512;
                float yval = ((ortriangle->GetPoint(0)->y+scaley)/(scaley*2))*512;
                
                float xvala = ((ortriangle->GetPoint(1)->x+scalex)/(scalex*2))*512;
                float yvala = ((ortriangle->GetPoint(1)->y+scaley)/(scaley*2))*512;
                
                float xvalb = ((ortriangle->GetPoint(2)->x+scalex)/(scalex*2))*512;
                float yvalb = ((ortriangle->GetPoint(2)->y+scaley)/(scaley*2))*512;
                
                
                triangulatedMesh.addTexCoord(ofVec2f(xval,yval));
                triangulatedMesh.addTexCoord(ofVec2f(xvala,yvala));
                triangulatedMesh.addTexCoord(ofVec2f(xvalb,yvalb));
            }
        }
        
        
    }
    delete cdt;
    cdt=NULL;
}
