//
//  ResizingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#include "ResizingMode.h"
#include "Logger.h"

std::vector<std::string> ResizingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer resize this");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    
    return commands;
}

ResizingMode::ResizingMode() : AirControlMode(){}

ResizingMode::~ResizingMode(){}

void ResizingMode::drawMode()
{
    if (resizingObject == NULL) return;
    
    ofPushMatrix();
    ofTranslate(originalCenterOfResizing);
    ofDrawBitmapString("Scale: " + ofToString(round(resizingObject->getScale() * 100)/100), ofPoint(0,0,0));
    ofNoFill();
    ofSetColor(255,255,255,128);
    ofLine(ofPoint(0,0,0), ofPoint(relativePosition.x, 0, relativePosition.z));
    ofLine(ofPoint(relativePosition.x, 0, relativePosition.z), relativePosition);
    float radius = ofPoint(relativePosition.x, 0, relativePosition.z).length();
    ofSetColor(255,255,0);
    ofRotate(90, 1, 0 , 0);
    ofCircle(0, 0, radius);
    ofFill();
    ofPopMatrix();
}

bool ResizingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "resize this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            resizingObject = highlightedObject;
            originalScale = resizingObject->getScale();
            
            // initialize scaling parameters
            originalPosition = handProcessor.getHandAtIndex(0)->getTipLocation();
            originalCenterOfResizing = resizingObject->getPosition();
            relativePosition = originalPosition - originalCenterOfResizing;
            
            originalDistance = ofPoint(relativePosition.x, relativePosition.z).length();
            
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

void ResizingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        resizingObject->setScale(originalScale);
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            // update scaling params
            relativePosition = handProcessor.getHandAtIndex(0)->getTipLocation() - originalCenterOfResizing;
            
            float currentDistance = ofPoint(relativePosition.x, relativePosition.z).length();
            
            resizingObject->setScale(currentDistance/originalDistance * originalScale);
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
    if (hasCompleted) {
        resizingObject = NULL;
    }
}

std::string ResizingMode::getStatusMessage()
{
    if (NULL != resizingObject) {
        std::stringstream msg;
        msg << "Resizing ";
        msg << resizingObject->getDescription();
        msg << " FROM ";
        msg << originalScale;
        msg << " TO ";
        msg << resizingObject->getScale();
        
        return msg.str();
    }
    return "Resizing xxx FROM xxx TO xxx";
}

std::string ResizingMode::getHelpMessage()
{
    return "not implemented";
}
