//
//  MovingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 3/31/15.
//
//

#include "MovingMode.h"
#include "Logger.h"

std::vector<std::string> MovingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer move this");
    commands.push_back("computer place");
    commands.push_back("computer cancel");
    
    return commands;
}

MovingMode::MovingMode() : AirControlMode()
{
    
}

MovingMode::~MovingMode()
{
    
}

void MovingMode::drawMode()
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
    if (hasCompleted)
    {
        movingObject = NULL;
    }
}

std::string MovingMode::getStatusMessage()
{
    if (NULL != movingObject)
    {
        std::stringstream msg;
        msg << "MOVING ";
        msg << movingObject->getDescription();
        msg << " FROM ";
        msg << originalPosition;
        msg << " TO ";
        msg << movingObject->getPosition();
        
        return msg.str();
    }
    return "MOVING xxx FROM xxx TO xxx";
}

std::string MovingMode::getHelpMessage()
{
    return "not implemented";
}
