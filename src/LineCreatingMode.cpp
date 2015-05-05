//
//  LineCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 5/4/15.
//
//


#include "LineCreatingMode.h"

#include "AirCommandLine.h"
#include "logger.h"


#define DEFAULT_LENGTH 20

std::vector<std::string> LineCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer " + drawCommand);
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

LineCreatingMode::LineCreatingMode() : AirControlMode(), line(NULL)
{
    traces.resize(2, ofPoint());
}

LineCreatingMode::~LineCreatingMode()
{
    
}

void LineCreatingMode::drawMode()
{

}


bool LineCreatingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == drawCommand)
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        traces[0] = hand-> getTipLocation() - ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        traces[1] = hand-> getTipLocation() + ofPoint(DEFAULT_LENGTH, DEFAULT_LENGTH, DEFAULT_LENGTH);
        if (!createLine(controller, objectManager))
        {
            Logger::getInstance()->temporaryLog("Drawing line FAILED; cannot allocate new copy");
            hasCompleted = true;
            return false;
        }
        
        hasCompleted = false;
        return true;
    }
    hasCompleted = true;
    return false;
}

void LineCreatingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    
    
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
            objectManager.updateHighlight(tipLocation, line);
            traces[1] = hand->getTipLocation();
            Logger::getInstance()->temporaryLog("Came inside hand active.");
            line -> updateEndPoints(getStartPoint(), getEndPoint());
        }
        else
        {
            // hand is lost
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
    }
    
}


bool LineCreatingMode::createLine(AirController* controller, AirObjectManager &objectManager)
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
        line = cmd -> getObject();
        return true;
    }
    return false;
}


std::string LineCreatingMode::getStatusMessage()
{
    if (NULL != line)
    {
        std::stringstream msg;
        msg << "Drawing Line ";
        msg << line->getDescription();
        msg << "\n at ";
        msg << line->getPosition();
        msg << "\n with length";
        msg << line -> getLength();
    }
        return "Drawing Line: move finger/hand to resize";
}


std::string LineCreatingMode::getHelpMessage()
{
    std::string msg ="When finished, say 'computer done' or to cancel, say 'computer cancel' \n";

    return msg;
}
