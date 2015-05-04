//
//  GrabMovingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "GrabMovingMode.h"

#include "AirCommandMoving.h"
#include "Logger.h"

std::vector<std::string> GrabMovingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer move");
    commands.push_back("computer cancel");
    return commands;
}

GrabMovingMode::GrabMovingMode() : AirControlMode()
{
    
}

GrabMovingMode::~GrabMovingMode()
{
    
}

void GrabMovingMode::drawMode()
{
    
}

bool GrabMovingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "move")
    {
        movingObject = NULL;
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}

void GrabMovingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    LeapHand* hand = handProcessor.getHandAtIndex(0);
    
    if (movingObject == NULL)
    {
        objectManager.updateHighlight(hand->getTipLocation());
        
        if (command == "cancel")
        {
            hasCompleted = true;
            Logger::getInstance()->logToFile("grab-move-canceled", startTime, ofGetElapsedTimeMillis());
        }
        else
        {
            if (hand->getIsPinching())
            {
                AirObject * highlightedObject = objectManager.getHighlightedObject();
                if (highlightedObject)
                {
                    movingObject = highlightedObject;
                    originalPosition = movingObject->getPosition();
                    offset = handProcessor.getHandAtIndex(0)->getTipLocation() - originalPosition;
                }
            }

        }
    }
    else // is currently moving something
    {
        if (command == "cancel")
        {
            movingObject->setPosition(originalPosition);
            hasCompleted = true;
            
            Logger::getInstance()->logToFile("grab-move-canceled", startTime, ofGetElapsedTimeMillis());

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
                    movingObject->setPosition(hand->getTipLocation()-offset);
                }
                else
                {
                    // hand is lost
                    hasCompleted = true;
                }
            }
        }
    }
    
    if (hasCompleted)
    {
        if (movingObject)
        {
            AirCommandMoving* cmd = new AirCommandMoving(movingObject, originalPosition, movingObject->getPosition());
            controller->pushCommand(cmd);
            movingObject = NULL;
            
            Logger::getInstance()->logToFile("grab-move", startTime, ofGetElapsedTimeMillis());
        }
    }
}

std::string GrabMovingMode::getStatusMessage()
{
    if (NULL != movingObject)
    {
        std::stringstream msg;
        msg << "Moving ";
        msg << movingObject->getDescription();
        return msg.str();
    }
    return "MOVE: Pinch to move object";
}

std::string GrabMovingMode::getHelpMessage()
{
    std::string msg =
    "Place the object then release pinch.\n"
    ;
    return msg;
}
