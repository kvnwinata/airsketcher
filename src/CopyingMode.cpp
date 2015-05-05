//
//  CopyingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "CopyingMode.h"

#include "AirCommandCopying.h"
#include "Logger.h"

std::vector<std::string> CopyingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer copy this");
    commands.push_back("computer place");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}


CopyingMode::CopyingMode()
: AirControlMode()
, objectCopy(NULL)
, copiedObject(NULL)
{
    
}

CopyingMode::~CopyingMode()
{
    
}

void CopyingMode::drawMode()
{
    
}

bool CopyingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "copy this")
    {
        // Try activate
        AirObject* highlightedObject = objectManager.getHighlightedObject();
        
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
            startTime = ofGetElapsedTimeMillis();
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'COPY THIS'");
            hasCompleted = true;
            return false;
        }
    }
    hasCompleted = true;
    return false;
}

void CopyingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    bool lost = false;
    
    if (command == "place" || command == "done")
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
            lost = true;
        }
    }
    if (hasCompleted) {
        if (isCancelled) {
            if (NULL != copiedObject) {
                controller->popCommand();                
            }
        } 
        copiedObject = NULL;
        objectCopy = NULL;
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
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
    "Then say 'computer done' to place the new object. \n\n"
    "OR to cancel midway, say 'computer cancel'. \n";
    return msg;
}
