//
//  LineCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "GrabLineCreatingMode.h"

#include "AirCommandLine.h"
#include "logger.h"


#define DEFAULT_LENGTH 20

std::vector<std::string> GrabLineCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer " + drawCommand);
    return commands;
}

GrabLineCreatingMode::GrabLineCreatingMode() : AirControlMode(), line(NULL), drawLineMode(NONE)
{
    traces.resize(2, ofPoint());
}

GrabLineCreatingMode::~GrabLineCreatingMode()
{

}

void GrabLineCreatingMode::drawMode()
{

}

bool GrabLineCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
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

void GrabLineCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
            objectManager.updateHighlight(tipLocation, line);

            if (hand->getIsPinching())
            {
                switch (drawLineMode) {
                    case DRAW:
                        traces[1] = hand->getTipLocation();
                        line->updateEndPoints(getStartPoint(), getEndPoint());
                        break;
                    case NONE:
                        traces[0] = hand-> getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        traces[1] = hand-> getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
                        if (!createLine(controller, objectManager))
                        {
                            Logger::getInstance()->temporaryLog("Drawing line FAILED; cannot allocate new copy");
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
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
    }
    
}


bool GrabLineCreatingMode::createLine(AirController* controller, AirObjectManager &objectManager)
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


std::string GrabLineCreatingMode::getStatusMessage()
{
    switch (drawLineMode) {
        case DRAW:
        {
            std::stringstream msg;
            msg << "Drawing Line ";
            msg << line->getDescription();
            msg << "\n at ";
            msg << line->getPosition();
            msg << "\n with length";
            msg << line -> getLength();
        }
        case DONE:
            return "Drawing Line: done";
        default:
            return "Drawing Line: release pinch when done";
    }
}


std::string GrabLineCreatingMode::getHelpMessage()
{
    std::string msg = "";
    switch (drawLineMode){
        case DRAW:
            msg ="When finished, slowly release your pinch \n";
            break;
        case NONE:
            msg = "Pinch your all fingers together to start then pull your line. \n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}
