//
//  GrabRotatingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "GrabRotatingMode.h"

#include "AirCommandRotating.h"
#include "Logger.h"

std::vector<std::string> GrabRotatingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer rotate");
    commands.push_back("computer cancel");
    
    return commands;
}

GrabRotatingMode::GrabRotatingMode() : AirControlMode(){}

GrabRotatingMode::~GrabRotatingMode(){}

void GrabRotatingMode::drawMode()
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

bool GrabRotatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "rotate")
    {
        rotatingObject = NULL;
        hasCompleted = false;
        return true;
    }
    return false;
}

void GrabRotatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    bool canceled = false;
    bool lost = false;

    std::string command = speechProcessor.getLastCommand();
    LeapHand* hand = handProcessor.getHandAtIndex(0);
    
    if (rotatingObject == NULL)
    {
        objectManager.updateHighlight(hand->getTipLocation());
        
        if (command == "cancel")
        {
            hasCompleted = true;
            canceled = true;
        }
        else
        {
            if (hand->getIsPinching())
            {
                AirObject * highlightedObject = objectManager.getHighlightedObject();
                if (highlightedObject)
                {
                    rotatingObject = highlightedObject;
                    
                    // initialize scaling parameters
                    originalOrientation = rotatingObject->getOrientation();
                    originalVector = handProcessor.getHandAtIndex(0)->getTipLocation() - rotatingObject->getPosition();
                    currentVector = originalVector;
                    
                    hasCompleted = false;
                    startTime = ofGetElapsedTimeMillis();
                    return true;
                }
            }
            
        }
    }
    else // is currently moving something
    {
        if (command == "cancel")
        {
            rotatingObject->setOrientation(originalOrientation);
            hasCompleted = true;
            canceled = true;
        }
        else
        {
            if (!hand->getIsPinching())
            {
                hasCompleted = true;
            }
            else
            {
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
                    lost = true;
                }
            }
        }
    }
    
    if (hasCompleted)
    {
        if (rotatingObject)
        {
            AirCommandRotating* cmd = new AirCommandRotating(rotatingObject, originalOrientation, rotatingObject->getOrientation());
            controller->pushCommand(cmd);
            rotatingObject = NULL;
        }
        
        Logger::getInstance()->logToFile(canceled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());

    }
}

std::string GrabRotatingMode::getStatusMessage()
{
    if (NULL != rotatingObject) {
        std::stringstream msg;
        msg << "ROTATING ";
        msg << rotatingObject->getDescription();
        
        return msg.str();
    }
    return "Rotating";
}

std::string GrabRotatingMode::getHelpMessage()
{
    if (rotatingObject)
    {
        return "Rotate the object, then release pinch.\nOr say 'computer cancel'";
    }
    else
    {
        return "Pinch an object to rotate.\nOr say 'computer cancel'";
    }
}
