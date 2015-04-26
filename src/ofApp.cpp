#include "ofApp.h"

#include "Logger.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    ofBackground(60, 60, 60);
    
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
    
    text.loadFont("verdana.ttf", 24);
    
    Logger::getInstance()->temporaryLog("Welcome to AirSketcher!");
    displayHelp = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    handProcessor.update();
    controller.update(handProcessor, speechProcessor, objectManager);
    
    //Logger::getInstance()->temporaryLog("test");
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
    ofDrawBitmapString(handProcessor.getStatusMessage(), 10, ofGetHeight()-20);
    ofDrawBitmapString(speechProcessor.getStatusMessage(), 10, ofGetHeight()-35);
    ofDrawBitmapString("FPS: " + ofToString(round(ofGetFrameRate() * 10) / 10), ofGetWidth() - 90, ofGetHeight()-20);
    
    //ofDrawBitmapString("HELP:", 10, ofGetHeight()*0.75-20);
    //ofDrawBitmapString(controller.getHelpMessage(), 10, ofGetHeight()*0.75);
    
    ofTranslate(10,ofGetWindowHeight()/2);
    //Logger::getInstance()->print();
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/4, ofGetHeight()/16);
    ofNoFill();
    ofRect(0,0, ofGetWidth()/2, ofGetHeight()/16);
    ofFill();
    //ofScale(5,5);
    ofPushMatrix();
    ofTranslate(20, 38);
    text.drawString(controller.getStatusMessage(), 0, 0);
    ofTranslate(0, 30);
    ofScale(0.4,0.4);
    text.drawString(controller.getHelpMessage(), 0, 0);
    ofPopMatrix();
    
    ofTranslate(20, -10);
    ofScale(0.5,0.5);
    ofSetColor(255,255,0);
    text.drawString(Logger::getInstance()->getTempMessage(), 0, 0);
    ofPopMatrix();
    
    displayHelpMessage();
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
    
    if (key == 'h')
    {
        displayHelp = !displayHelp;
    }
}

void ofApp::displayHelpMessage()
{
    if(!displayHelp) return;
    std::stringstream msg;
    
    msg << "[ HELP ]\n\nPress 'h' again to hide.\n";
    msg << "\n";
    msg << "To undo             : say 'computer undo'\n";
    msg << "To redo             : say 'computer redo'\n";
    

    msg << "\n";
    msg << "To draw a sphere    : say 'computer draw sphere'\n";
    msg << "To draw a cylinder  : say 'computer draw cylinder'\n";
    msg << "To draw a line      : say 'computer draw line'\n";
    msg << "\n";
    msg << "To move     : select object + say 'computer move this'\n";
    msg << "To resize   : select object + say 'computer resize this'\n";
    msg << "To rotate   : select object + say 'computer rotate this'\n";
    msg << "To erase    : select object + say 'computer erase this'\n";
    msg << "To color    : select object + say 'computer color this [color]'\n";
    msg << "\n";
    msg << "To change point of view: pinch using both hands";

    ofPushMatrix();

    ofTranslate(ofGetWidth()/4-15, ofGetHeight()/2 + 50);
    ofSetColor(20, 20, 20, 200);
    ofRect(0, 0, ofGetWidth()/2+30, ofGetHeight()/2);
    
    ofScale(0.5,0.5);
    ofSetColor(255,255,255, 200);
    ofDrawBitmapString(msg.str(), 30,50);
    //text.drawString(msg.str(), 20, 40);
    
    ofPopMatrix();
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
