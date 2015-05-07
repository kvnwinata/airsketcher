//
//  GrabSnapObjectsMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/29/15.
//
//

#include "GrabSnapObjectsMode.h"

#include "AirCommandLine.h"
#include "logger.h"


#define DEFAULT_LENGTH 20

std::vector<std::string> GrabSnapObjectsMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer " + drawCommand);
    return commands;
}

GrabSnapObjectsMode::GrabSnapObjectsMode() : AirControlMode(), line(NULL), drawLineMode(NONE)
{
    traces.resize(2, ofPoint());
    snapped = false;
}

GrabSnapObjectsMode::~GrabSnapObjectsMode()
{
    
}

void GrabSnapObjectsMode::drawMode()
{
    if (drawLineMode == DRAW)
    {
        line -> updateEndPoints(getStartPoint(), getEndPoint());
    }
}


bool GrabSnapObjectsMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void GrabSnapObjectsMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;
    
    if (command == "cancel")
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
            
            if (hand->getIsPinching())
            {
                switch (drawLineMode) {
                    case DRAW:
                        traces[1] = hand->getTipLocation();
                        // if object is highlighted
                        if (highlightedObject){
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
                                if (objDescr.compare(lineObjDescr) != 0 && objDescr.compare(snappedFirstObj) != 0){
                                    traces[1] = highlightPosition;
                                }
                                
                            }
                        }
                        line->updateEndPoints(getStartPoint(), getEndPoint());
                        lineObjDescr = line->getDescription();
                        break;
                    case NONE:
                        traces[0] = hand-> getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        traces[1] = hand-> getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        if (!createLine(controller, objectManager))
                        {
                            Logger::getInstance()->temporaryLog("Snapping FAILED; cannot allocate new copy");
                            hasCompleted = true;
                        }
                        drawLineMode = DRAW;
                        break;
                    default:
                        break;
                }
            }
            else if (drawLineMode == DRAW)
            {
                drawLineMode = DONE;
                hasCompleted = true;
            }
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
        drawLineMode = NONE;
        traces.resize(2, ofPoint());
        startPoint = ofPoint();
        endPoint = ofPoint();
        snappedFirstObj = "";
        lineObjDescr = "";
        snapped = false;
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
}


bool GrabSnapObjectsMode::createLine(AirController* controller, AirObjectManager &objectManager)
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


std::string GrabSnapObjectsMode::getStatusMessage()
{
    switch (drawLineMode) {
        case DRAW:
        {
            return "SNAP LINE: Drawing";
        }
        case DONE:
            return "SNAP LINE: done";
        default:
            return "SNAP LINE: Pinch to draw.";
    }
}


std::string GrabSnapObjectsMode::getHelpMessage()
{
    std::string msg = "";
    switch (drawLineMode){
        case DRAW:
            msg ="Object snapped. Release pinch slowly when done. \n";
            break;
        case NONE:
            msg = "Select an object to start then pull your line. \n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}

