//
//  MovingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#include "MovingMode.h"
#include "Logger.h"

MovingMode::MovingMode() : AirControlMode()
{
    
}

MovingMode::~MovingMode()
{
    
}

void MovingMode::drawMode() const
{
    
}

bool MovingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "move this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();

        if (highlightedObject)
        {
            movingObject = highlightedObject;
            originalPosition = movingObject->getPosition();
            
            hasCompleted = false;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'MOVE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void MovingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "place")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        movingObject->setPosition(originalPosition);
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            movingObject->setPosition(hand->getTipLocation());
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
}

std::string MovingMode::getStatusMessage()
{
    return "MOVING xxxx FROM xxx TO xxx";
}