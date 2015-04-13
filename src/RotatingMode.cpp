//
//  RotatingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "RotatingMode.h"

#include "Logger.h"

std::vector<std::string> RotatingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer rotate this");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    
    return commands;
}

RotatingMode::RotatingMode() : AirControlMode(){}

RotatingMode::~RotatingMode(){}

void RotatingMode::drawMode()
{
    if (rotatingObject == NULL) return;
    
    ofPushMatrix();
    ofTranslate(rotatingObject->getPosition());
    
    ofVec3f euler = rotatingObject->getOrientation().getEuler();
    std::stringstream msg;
    msg << "Rotation:\n";
    msg << "X: " << round(euler.x * 100)/100 << std::endl;
    msg << "Y: " << round(euler.y * 100)/100 << std::endl;
    msg << "Z: " << round(euler.z * 100)/100 << std::endl;
    ofDrawBitmapString(msg.str(), ofPoint(0,0,0));
    
    ofNoFill();
    ofSetColor(255,255,255,128);
    ofLine(ofPoint(0,0,0), currentVector);
    ofSetColor(0,0,255,255);
    ofLine(ofPoint(0,0,0), originalVector);
    
    float rotationAngle;
    ofVec3f rotationAxis;
    rotatingObject->getOrientation().getRotate(rotationAngle, rotationAxis);
    
    ofRotate(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
    
    // coordinate axis
    ofSetLineWidth(5.f);
    ofSetColor(255, 0, 0); ofLine(ofPoint(0,0,0), ofPoint(200,0,0));
    ofSetColor(0, 255, 0); ofLine(ofPoint(0,0,0), ofPoint(0,200,0));
    ofSetColor(0, 0, 255); ofLine(ofPoint(0,0,0), ofPoint(0,0,200));
    ofSetLineWidth(1.f);
    
    float radius = currentVector.length();
    ofSetColor(255,255,0);
    ofCircle(0,0, radius);
    ofRotate(90, 1, 0 , 0);
    ofCircle(0, 0, radius);
    ofRotate(90, 0, 1 , 0);
    ofCircle(0, 0, radius);
    ofFill();
    ofPopMatrix();
}

bool RotatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "rotate this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            rotatingObject = highlightedObject;
            
            // initialize scaling parameters
            originalOrientation = rotatingObject->getOrientation();
            originalVector = handProcessor.getHandAtIndex(0)->getTipLocation() - rotatingObject->getPosition();
            currentVector = originalVector;
            
            hasCompleted = false;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'RESIZE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void RotatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        rotatingObject->setOrientation(originalOrientation);
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            // update rotating params
            currentVector = handProcessor.getHandAtIndex(0)->getTipLocation() - rotatingObject->getPosition();
            
            float rotationAngle;
            ofVec3f rotationAxis;
            rotationAxis = originalVector.crossed(currentVector).normalized();
            rotationAngle = originalVector.angle(currentVector);
            
            ofQuaternion currentRotation;
            currentRotation.makeRotate(rotationAngle, rotationAxis);
            rotatingObject->setOrientation(originalOrientation * currentRotation);
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
    if (hasCompleted) {
        rotatingObject = NULL;
    }
}

std::string RotatingMode::getStatusMessage()
{
    if (NULL != rotatingObject) {
        std::stringstream msg;
        msg << "Rotating ";
        msg << rotatingObject->getDescription();
        msg << " FROM ";
        msg << "XXX";
        msg << " TO ";
        //msg << rotatingObject->getScale();
        
        return msg.str();
    }
    return "Rotating";
}

std::string RotatingMode::getHelpMessage()
{
    std::string msg =
    ""
    ;
    return msg;
}
