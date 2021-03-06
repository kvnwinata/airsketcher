//
//  ResizingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#include "ResizingMode.h"

#include "AirCommandResizing.h"
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

bool ResizingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
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
            startTime = ofGetElapsedTimeMillis();
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

void ResizingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
    bool canceled = false;
    bool lost = false;

    std::string command = speechProcessor.getLastCommand();
    
    if (command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        resizingObject->setScale(originalScale);
        hasCompleted = true;
        canceled = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            // update scaling params
            relativePosition = handProcessor.getHandAtIndex(0)->getTipLocation() - originalCenterOfResizing;
            float currentDistance = ofPoint(relativePosition.x, relativePosition.z).length();
            float newScale = currentDistance/originalDistance * originalScale;
            resizingObject->setScale(newScale);         
        }
        else
        {
            // hand is lost
            hasCompleted = true;
            lost = true;
        }
    }
    if (hasCompleted) {
        AirCommandResizing* cmd = new AirCommandResizing(resizingObject, originalScale, resizingObject->getScale());
        controller->pushCommand(cmd);
        resizingObject = NULL;
        
        Logger::getInstance()->logToFile(canceled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());

    }
}

std::string ResizingMode::getStatusMessage()
{
    if (NULL != resizingObject) {
        std::stringstream msg;
        msg << "Resizing ";
        msg << resizingObject->getDescription();
        return msg.str();
    }
    return "Resizing";
}

std::string ResizingMode::getHelpMessage()
{
    std::string msg =
    "Adjust the size by moving your hand, then say 'computer done'\n"
    "OR say 'computer cancel' if you change your mind"
    ;
    return msg;
}
