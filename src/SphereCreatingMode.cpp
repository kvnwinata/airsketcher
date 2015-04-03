//
//  SphereCreatingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "SphereCreatingMode.h"
#include "Logger.h"

std::vector<std::string> SphereCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    return commands;
}

SphereCreatingMode::SphereCreatingMode() : AirControlMode()
{
    
}

SphereCreatingMode::~SphereCreatingMode()
{
    
}

void SphereCreatingMode::drawMode()
{
    
}

bool SphereCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
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

void SphereCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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

std::string SphereCreatingMode::getStatusMessage()
{
    return "MOVING xxxx FROM xxx TO xxx";
}