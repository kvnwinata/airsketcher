//
//  GrabResizingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#include "GrabResizingMode.h"

#include "AirCommandResizing.h"
#include "Logger.h"

std::vector<std::string> GrabResizingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer resize");
    commands.push_back("computer cancel");
    
    return commands;
}

GrabResizingMode::GrabResizingMode() : AirControlMode(){}

GrabResizingMode::~GrabResizingMode(){}

void GrabResizingMode::drawMode()
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

bool GrabResizingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "resize")
    {
        hasCompleted = false;
        resizingObject = NULL;
        return true;
    }
    return false;
}

void GrabResizingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    bool canceled = false;
    bool lost = false;

    std::string command = speechProcessor.getLastCommand();
    
    if (resizingObject == NULL)
    {
        objectManager.updateHighlight(handProcessor.getHandAtIndex(0)->getTipLocation());
    }
    
    if (command == "cancel")
    {
        if (resizingObject)
        {
            resizingObject->setScale(originalScale);
        }
        hasCompleted = true;
        canceled = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);

        if (resizingObject) // has grabbed an object
        {
            
            if (hand->getIsPinching())
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
        else if (hand->getIsPinching())
        {
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
            }
        }
    }
    if (hasCompleted) {
        if (resizingObject)
        {
            AirCommandResizing* cmd = new AirCommandResizing(resizingObject, originalScale, resizingObject->getScale());
            controller->pushCommand(cmd);
            resizingObject = NULL;
            
        }
        Logger::getInstance()->logToFile(canceled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}

std::string GrabResizingMode::getStatusMessage()
{
    if (NULL != resizingObject)
    {
        std::stringstream msg;
        msg << "Resizing ";
        msg << resizingObject->getDescription();
        return msg.str();
    }
    return "RESIZE: Pinch to resize object";
}

std::string GrabResizingMode::getHelpMessage()
{
    std::string msg =
    "Adjust the size by moving your hand then release pinch'\n"
    "OR say 'computer cancel' if you change your mind"
    ;
    return msg;
}
