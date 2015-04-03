//
//  ScalingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "ScalingMode.h"
#include "Logger.h"

std::vector<std::string> ScalingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer scale this");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    
    return commands;
}

ScalingMode::ScalingMode() : AirControlMode(){}

ScalingMode::~ScalingMode(){}

void ScalingMode::drawMode()
{
    if (scalingObject == NULL) return;
    
    ofPushMatrix();
    ofTranslate(originalCenterOfScaling);
    ofSetColor(255,255,0);
    ofNoFill();

    ofLine(ofPoint(0,0,0), relativePosition);
    ofLine(ofPoint(0,0,0), ofPoint(relativePosition.x, relativePosition.y, 0));
    ofCircle(ofPoint(0,0,relativePosition.z), ofPoint(relativePosition.x, relativePosition.y).length());
    ofLine(ofPoint(relativePosition.x, relativePosition.y, 0), relativePosition);
    
    float radius = relativePosition.length();
    ofCircle(0, 0, radius);
    ofRotate(90, 1, 0 , 0);
    ofCircle(0, 0, radius);
    ofRotate(90, 0, 1, 0);
    ofCircle(0, 0, radius);
    
    ofFill();
    ofPopMatrix();
}

bool ScalingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "scale this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            scalingObject = highlightedObject;
            originalScale = scalingObject->getScale();
            
            originalPosition = handProcessor.getHandAtIndex(0)->getTipLocation();
            originalCenterOfScaling = originalPosition + (scalingObject->getPosition() - originalPosition).normalized() * scalingParameter;
            relativePosition = originalPosition - originalCenterOfScaling;
            //Logger::getInstance()->log(ofToString();
            
            hasCompleted = false;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'SCALE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void ScalingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        scalingObject->setScale(originalScale);
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            relativePosition = handProcessor.getHandAtIndex(0)->getTipLocation() - originalCenterOfScaling;
            float currentDistance = relativePosition.length();
            
            scalingObject->setScale(currentDistance/scalingParameter * originalScale);
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
    if (hasCompleted) {
        scalingObject = NULL;
    }
}

std::string ScalingMode::getStatusMessage()
{
    if (NULL != scalingObject) {
        std::stringstream msg;
        msg << "Scaling ";
        msg << scalingObject->getDescription();
        msg << " FROM ";
        msg << originalScale;
        msg << " TO ";
        msg << scalingObject->getScale();
        
        return msg.str();
    }
    return "Scaling xxx FROM xxx TO xxx";
}