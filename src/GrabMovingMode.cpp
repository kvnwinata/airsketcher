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
    
    AirObject * highlightedObject = objectManager.getHighlightedObject();
    LeapHand * hand = handProcessor.getHandAtIndex(0);
    
    if (highlightedObject && hand->getIsPinching())
    {
        movingObject = highlightedObject;
        originalPosition = movingObject->getPosition();
        offset = hand->getTipLocation() - originalPosition;
        
        hasCompleted = false;
        return true;
    }
    else if (highlightedObject == NULL)
    {
        //Logger::getInstance()->temporaryLog("Pinch an object to move");
        hasCompleted = true;
        return false;
    }
    
    return false;
}

void GrabMovingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    LeapHand* hand = handProcessor.getHandAtIndex(0);
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
    if (hasCompleted)
    {
        AirCommandMoving* cmd = new AirCommandMoving(movingObject, originalPosition, movingObject->getPosition());
        controller->pushCommand(cmd);
        movingObject = NULL;
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
    return "";
}

std::string GrabMovingMode::getHelpMessage()
{
    std::string msg =
    "Place the object then release pinch.\n"
    ;
    return msg;
}
