//
//  MovingMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15.
//
//

#include "MovingMode.h"

#include "AirCommandMoving.h"
#include "Logger.h"

std::vector<std::string> MovingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer move this");
    commands.push_back("computer place");
    commands.push_back("computer done");
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

bool MovingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "move this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            movingObject = highlightedObject;
            originalPosition = movingObject->getPosition();
            offset = handProcessor.getHandAtIndex(0)->getTipLocation() - originalPosition;
            
            hasCompleted = false;
            startTime = ofGetElapsedTimeMillis();
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'MOVE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    hasCompleted = true;
    return false;
}

void MovingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    bool canceled = false;
    bool lost = false;
    
    std::string command = speechProcessor.getLastCommand();
    
    if (command == "place" || command == "done")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        movingObject->setPosition(originalPosition);
        hasCompleted = true;
        canceled = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            movingObject->setPosition(hand->getTipLocation()-offset);
        }
        else
        {
            // hand is lost
            hasCompleted = true;
            lost = true;
        }
    }
    if (hasCompleted)
    {
        AirCommandMoving* cmd = new AirCommandMoving(movingObject, originalPosition, movingObject->getPosition());
        controller->pushCommand(cmd);
        movingObject = NULL;
        
        Logger::getInstance()->logToFile(canceled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());

    }
}

std::string MovingMode::getStatusMessage()
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

std::string MovingMode::getHelpMessage()
{
    std::string msg =
//    "1. Point at the object you'd like to move. \n"
//    "2. Say 'computer move this'. \n"
//    "3. Move your hand to a new position while still pointing at the object. \n"
//    "4. Then say 'computer done' to place the object. \n"
//    "4. To cancel midway (before placing the object), say 'computer cancel'. \n";
    "Place the object, then say 'computer done'\n"
    "\nOR say 'computer cancel' to cancel midway"
    ;
    return msg;
}
