#pragma once

#include "ofMain.h"

#include "AirObjectManager.h"
#include "HandProcessor.h"
#include "SpeechProcessor.h"
#include "AirController.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private: // Air Sketcher Main Components
    
    AirObjectManager    objectManager;

    HandProcessor       handProcessor;
    SpeechProcessor     speechProcessor;
    
    AirController       controller;
    
private:
    ofCamera            cam;
    ofEasyCam           ecam;
    
    ofLight             pointLight;
    ofMaterial          material;
};
