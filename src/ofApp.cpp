#include "ofApp.h"

#include "Logger.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(40, 40, 40);
    
    // Main components setup
    
    
    // add words to dictionary
    speechProcessor.setup(controller.getCommands());
    
    // OF setup
    cam.setupPerspective();
    cam.setPosition(0, 700, 400);
    cam.lookAt(ofVec3f(0,0,300));
    
    pointLight.setPosition(0, 2000, 1000);
    pointLight.lookAt(ofVec3f(0,0,500));
    pointLight.setDiffuseColor(ofColor(255,255,255));
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    
    //material.setShininess(2.f);
    material.setAmbientColor(ofColor(255,255,255));
    material.setDiffuseColor(ofColor(255,255,255));
}

//--------------------------------------------------------------
void ofApp::update(){
    handProcessor.update();
    controller.update(handProcessor, speechProcessor, objectManager);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableLighting();
    
    cam.begin();
    pointLight.enable();
    material.begin();

    ofSetColor(255,255,255);
    //ofDrawSphere(0, 0, 0, 200);
    
    ofSetColor(255,0,0); ofLine(ofPoint(0,0,0), ofPoint(200,0,0));
    ofSetColor(0,255,0); ofLine(ofPoint(0,0,0), ofPoint(0,200,0));
    ofSetColor(0,0,255); ofLine(ofPoint(0,0,0), ofPoint(0,0,200));
    
    ofSetColor(255, 255, 255);
    
    handProcessor.drawHands();
    objectManager.drawObjects();
    controller.draw();
    
    material.end();
    pointLight.disable();
    cam.end();

    ofDisableLighting();
    ofDisableDepthTest();
    ofDisableAlphaBlending();
    
    // messages
    ofPushMatrix();
    ofSetColor(255,255,255);
    ofDrawBitmapString(handProcessor.getStatusMessage(), 10, 20);
    ofDrawBitmapString(speechProcessor.getStatusMessage(), 10, 35);
    ofDrawBitmapString(controller.getStatusMessage(), 10, 50);
    ofDrawBitmapString("FPS: " + ofToString(round(ofGetFrameRate() * 10) / 10), ofGetWidth() - 90, 20);
    
    ofDrawBitmapString(controller.getHelpMessage(), 10, ofGetHeight()*0.75);
    
    ofTranslate(10,ofGetWindowHeight()/2);
    Logger::getInstance()->print();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c')
    {
        AirSphere * sphere = new AirSphere();
        sphere->setup(ofPoint(-200,0,400), 100, ofColor(128,64,64));
        objectManager.addObject(sphere);
        
        AirBox * box = new AirBox();
        box->setup(ofPoint (0, 0, 300), ofVec3f(100, 200, 300), ofColor(50,50,255));
        objectManager.addObject(box);
        
        AirCylinder * cylinder = new AirCylinder();
        cylinder->setup(ofPoint (0, 0, 0), 200, 400, ofColor(50,50,255));
        objectManager.addObject(cylinder);
        
        AirLine * line = new AirLine();
        line->setup(ofPoint (0, 0, 0), ofPoint(100,200,300), ofColor(50,50,255));
        objectManager.addObject(line);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
