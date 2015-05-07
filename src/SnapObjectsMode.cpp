//
//  SnapObjectsMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 5/4/15.
//
//

#include "SnapObjectsMode.h"

#include "AirCommandLine.h"
#include "logger.h"


#define DEFAULT_LENGTH 20

std::vector<std::string> SnapObjectsMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer " + drawCommand);
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

SnapObjectsMode::SnapObjectsMode() : AirControlMode(), line(NULL)
{
    traces.resize(2, ofPoint());
    snapped = false;
}

SnapObjectsMode::~SnapObjectsMode()
{   
}

void SnapObjectsMode::drawMode()
{
}


bool SnapObjectsMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        Logger::getInstance()->temporaryLog("Came inside the try activate.");
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        traces[0] = hand-> getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        traces[1] = hand-> getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        if (!createLine(controller, objectManager))
        {
            Logger::getInstance()->temporaryLog("Snapping FAILED; cannot allocate new copy");
            hasCompleted = true;
            return false;
        }
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void SnapObjectsMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;
    
    if (command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        hasCompleted = true;
        isCancelled = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            // need to update higlighted object for snapping
            ofPoint tipLocation = hand->getTipLocation();
            objectManager.updateHighlight(tipLocation);
            
            AirObject* highlightedObject = objectManager.getHighlightedObject();
            ofPoint highlightPosition;
            std::string objDescr;

            traces[1] = hand->getTipLocation();
            // if object is highlighted
            if (highlightedObject)
            {
                highlightPosition = highlightedObject->getPosition();
                objDescr = highlightedObject->getDescription();
                if (!snapped)
                {
                    std::string snapDescr = "snapped with "+ objDescr;
                    Logger::getInstance()->temporaryLog(snapDescr);
                    traces[0] = highlightPosition;
                    snappedFirstObj = objDescr;
                    snapped = true;
                }
                else
                {
                    if (objDescr.compare(lineObjDescr) != 0 && objDescr.compare(snappedFirstObj) != 0)
                    {
                        traces[1] = highlightPosition;
                    }
                            
                }
                
            }
            line->updateEndPoints(getStartPoint(), getEndPoint());
            lineObjDescr = line->getDescription();
        }
        else
        {
            // hand is lost
            lost = true;
            hasCompleted = true;
        }
    }
    
    if (hasCompleted)
    {
        if (isCancelled) {
            if (NULL != line) {
                controller->popCommand();                
            }
        }
        line = NULL;
        traces.resize(2, ofPoint());
        startPoint = ofPoint();
        endPoint = ofPoint();
        snappedFirstObj = "";
        lineObjDescr = "";
        snapped = false;
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}


bool SnapObjectsMode::createLine(AirController* controller, AirObjectManager &objectManager)
{
    ofPoint startPoint = getStartPoint();
    ofPoint endPoint = getEndPoint();
    
    float dist = (endPoint - startPoint).length();
    if (dist != 0.0)
    {
        AirCommandLine* cmd = new AirCommandLine(objectManager, startPoint, endPoint);
        if (!controller->pushCommand(cmd))
        {
            return false;
        }
        line = cmd->getObject();
        return true;
    }
    
    return false;
}


std::string SnapObjectsMode::getStatusMessage()
{
    if (NULL != line)
    {
        std::stringstream msg;
        msg << "Snapping ";
        msg << line->getDescription();
        msg << "\n at ";
        msg << line->getPosition();
        msg << "\n with length";
        msg << line -> getLength();
    }
    return "Drawing Snap Line..";
}


std::string SnapObjectsMode::getHelpMessage()
{
    std::string msg =
    "Move outwards or inwards to resize.\n"
    "When finished, say 'computer done'\n"
    "OR to cancel midway, say 'computer cancel'\n";
    return msg;
}