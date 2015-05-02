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
    return commands;
}


GrabCopyingMode::GrabCopyingMode()
: AirControlMode()
, copyingMode(NONE)
, objectCopy(NULL)
, copiedObject(NULL)
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
        // Try activate
        AirObject* highlightedObject = objectManager.getHighlightedObject();
        if (highlightedObject)
        {
            copiedObject = highlightedObject;
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
    hasCompleted = true;
    return false;
}

void GrabCopyingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    bool isCancelled = false;
    
    if (command == "cancel")
    {
        isCancelled = true;
        hasCompleted = true;
    }
    else
    {
        LeapHand* hand = handProcessor.getHandAtIndex(0);
        
        if (hand->getIsActive())
        {
            if (hand->getIsPinching())
            {
                switch (copyingMode) {
                    case DRAW:
                        objectCopy->setPosition(hand->getTipLocation());
                        break;
                    case NONE:
                    {
                        AirCommandCopying* cmd = new AirCommandCopying(objectManager, copiedObject);
                        if (!controller->pushCommand(cmd))
                        {
                            Logger::getInstance()->temporaryLog("COPYing object " + copiedObject->getDescription() + "failed; cannot allocate new copy");
                        }
                        objectCopy = cmd->getObjectCopy();
                        copyingMode = DRAW;
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (copyingMode == DRAW)
            {
                copyingMode = DONE;
                hasCompleted = true;
            }
        }
        else
        {
            // hand is lost
            hasCompleted = true;
        }
    }
    if (hasCompleted) {
        if (isCancelled)
        {
            controller->popCommand();
        }
        copyingMode = NONE;
        copiedObject = NULL;
        objectCopy = NULL;
    }
}

std::string GrabCopyingMode::getStatusMessage()
{
    switch (copyingMode) {
        case DRAW:
        {
            std::stringstream msg;
            msg << "Copying ";
            msg << copiedObject->getDescription();
            msg << "\n from ";
            msg << copiedObject->getPosition();
            msg << "\n to ";
            msg << objectCopy->getPosition();
        }
        case DONE:
            return "Copying: done";
        default:
            return "Copying: do nothing";
    }
}

std::string GrabCopyingMode::getHelpMessage()
{
    std::string msg;
    switch (copyingMode){
        case NONE:
            msg = "Pinch your hand at an object to copy and move the copy around. \n";
            break;
        case DRAW:
            msg = "When finished, release your pinch\n OR to cancel midway, say 'computer cancel'\n";
            break;
        case DONE:
            msg = "You're done!";
            break;
    }
    return msg;
}