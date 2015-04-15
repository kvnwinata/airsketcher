//
//  SpaceSpaceRotatingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/5/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "SpaceRotatingMode.h"

#include "AirCommandSpaceRotating.h"
#include "AirCommand.h"
#include "Logger.h"

std::vector<std::string> SpaceRotatingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer cancel");
    
    return commands;
}

SpaceRotatingMode::SpaceRotatingMode() : AirControlMode()
{
    centerOfRotation = ofPoint(0, 0, 400);
}

SpaceRotatingMode::~SpaceRotatingMode(){}

void SpaceRotatingMode::drawMode()
{
    /*
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
    float radius = currentVector.length();
    ofSetColor(255,255,0);
    ofCircle(0,0, radius);
    ofRotate(90, 1, 0 , 0);
    ofCircle(0, 0, radius);
    ofRotate(90, 0, 1 , 0);
    ofCircle(0, 0, radius);
    ofFill();
    ofPopMatrix();
     */
}

bool SpaceRotatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    LeapHand * hand0 = handProcessor.getHandAtIndex(0);
    LeapHand * hand1 = handProcessor.getHandAtIndex(1);
    
    if (hand0->getIsPinching() && hand1->getIsPinching())
    {
        originalVector = hand0->getTipLocation() - hand1->getTipLocation();
        currentVector = originalVector;
        
        // clear original orientation and position vectors
        originalOrientations.clear();
        originalRelativePositions.clear();
        
        // store original orientations and positions
        std::vector<AirObject*>::iterator begin, end;
        objectManager.getObjectsIterator(begin, end);
        
        for (auto iter = begin; iter != end; iter++)
        {
            AirObject* object = *iter;
            originalRelativePositions.push_back(object->getPosition() - centerOfRotation);
            originalOrientations.push_back(object->getOrientation());
        }
        
        hasCompleted = false;
        return true;
    }
    return false; // do not enter mode
}

void SpaceRotatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "cancel")
    {
        // reset orientation
        hasCompleted = true;
        return;
    }
    
    // check exit condition:
    LeapHand * hand0 = handProcessor.getHandAtIndex(0);
    LeapHand * hand1 = handProcessor.getHandAtIndex(1);

    if (!(hand0->getIsPinching() && hand1->getIsPinching()))
    {
        hasCompleted = true;
    }
    else // rotate space
    {
        currentVector = hand0->getTipLocation() - hand1->getTipLocation();
        
        float rotationAngle;
        ofVec3f rotationAxis;
        rotationAxis = originalVector.crossed(currentVector).normalized();
        rotationAngle = originalVector.angle(currentVector);
        
        ofQuaternion currentRotation;
        currentRotation.makeRotate(rotationAngle, rotationAxis);
        
        // apply rotation to all objects
        std::vector<AirObject*>::iterator begin, end;
        objectManager.getObjectsIterator(begin, end);
        
        int index = 0;
        for (auto iter = begin; iter != end; iter++)
        {
            AirObject* object = *iter;
            object->setPosition(originalRelativePositions[index].rotated(rotationAngle, rotationAxis) + centerOfRotation);
            object->setOrientation(originalOrientations[index] * currentRotation);
            index++;
        }
    }
}

std::string SpaceRotatingMode::getStatusMessage()
{
    /*
    if (NULL != rotatingObject) {
        std::stringstream msg;
        msg << "Rotating ";
        //msg << rotatingObject->getDescription();
        msg << " FROM ";
        msg << "XXX";
        msg << " TO ";
        //msg << rotatingObject->getScale();
        
        return msg.str();
    }
     */
    return "CHANGING POINT OF VIEW";
}

std::string SpaceRotatingMode::getHelpMessage()
{
    return "Rotating the SPACE, release your pinch when you're done.";
}
