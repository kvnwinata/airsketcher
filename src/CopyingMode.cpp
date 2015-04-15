//
//  CopyingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CopyingMode.h"

#include "AirCommand.h"
#include "Logger.h"

std::vector<std::string> CopyingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer copy this");
    commands.push_back("computer place");
    commands.push_back("computer cancel");
    
    return commands;
}


CopyingMode::CopyingMode() : AirControlMode()
{
    
}

CopyingMode::~CopyingMode()
{
    
}

void CopyingMode::drawMode()
{
    
}

bool CopyingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "copy this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            copiedObject = highlightedObject;
            AirCommandCopying cmd(objectManager, copiedObject);
            cmd.execute();
            objectCopy = cmd.getObjectCopy();
            if (NULL == objectCopy)
            {
                Logger::getInstance()->temporaryLog("COPYing object " + copiedObject->getDescription() + "failed; cannot allocate new copy");
                hasCompleted = true;
                return false;
            }
            pushCommand(cmd);
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

void CopyingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
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
            AirCommand cmd = popCommand();
            cmd.unexecute();
        }
        copiedObject = NULL;
        objectCopy = NULL;
    }
}

std::string CopyingMode::getStatusMessage()
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

std::string CopyingMode::getHelpMessage()
{
    std::string msg =
    "Move the new object around.\n"
    "Then say 'computer place' to place the new object. \n\n"
    "OR to cancel midway, say 'computer cancel'. \n";
    return msg;
}
