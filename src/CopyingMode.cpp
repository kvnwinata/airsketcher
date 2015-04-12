//
//  CopyingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CopyingMode.h"
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
            objectCopy = highlightedObject->getCopy();
            if (NULL == objectCopy)
            {
                Logger::getInstance()->temporaryLog("COPYing object " + copiedObject->getDescription() + "failed; cannot allocate new copy");
                hasCompleted = true;
                return false;
            }
            objectManager.addObject(objectCopy);
            objectManager.switchHighlightedObject(objectCopy, objectCopy->getPosition());

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
            objectManager.deleteObject(objectCopy);
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
        msg << " FROM ";
        msg << copiedObject->getPosition();
        msg << " TO ";
        msg << objectCopy->getPosition();
        
        return msg.str();
    }
    return "COPYING xxx";
}

std::string CopyingMode::getHelpMessage()
{
    return "not implemented";
}
