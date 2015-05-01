//
//  GrabCopyingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 5/1/15.
//
//

#include "GrabCopyingMode.h"

#include "AirCommandCopying.h"
#include "Logger.h"

std::vector<std::string> GrabCopyingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer copy this");
    commands.push_back("computer place");
    commands.push_back("computer cancel");
    
    return commands;
}


GrabCopyingMode::GrabCopyingMode() : AirControlMode()
{
    
}

GrabCopyingMode::~GrabCopyingMode()
{
    
}

void GrabCopyingMode::drawMode()
{
    
}

bool GrabCopyingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "copy this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            copiedObject = highlightedObject;
            AirCommandCopying* cmd = new AirCommandCopying(objectManager, copiedObject);
            if (!controller->pushCommand(cmd))
            {
                Logger::getInstance()->temporaryLog("COPYing object " + copiedObject->getDescription() + "failed; cannot allocate new copy");
                hasCompleted = true;
                return false;
            }
            objectCopy = cmd->getObjectCopy();
            
            hasCompleted = false;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'COPY THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void GrabCopyingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    
    if (command == "place")
    {
        hasCompleted = true;
    }
    else if (command == "cancel")
    {
        isCancelled = true;
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            objectCopy->setPosition(hand->getTipLocation());
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
    if (hasCompleted) {
        if (isCancelled) {
            controller->popCommand();
        }
        copiedObject = NULL;
        objectCopy = NULL;
    }
}

std::string GrabCopyingMode::getStatusMessage()
{
    if ((NULL != copiedObject) && (objectCopy != NULL))
    {
        std::stringstream msg;
        msg << "COPYING ";
        msg << copiedObject->getDescription();
        msg << "\n FROM ";
        msg << copiedObject->getPosition();
        msg << "\n TO ";
        msg << objectCopy->getPosition();
        
        return msg.str();
    }
    return "";
}

std::string GrabCopyingMode::getHelpMessage()
{
    std::string msg =
    "Move the new object around.\n"
    "Then say 'computer place' to place the new object. \n\n"
    "OR to cancel midway, say 'computer cancel'. \n";
    return msg;
}