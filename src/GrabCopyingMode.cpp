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
    commands.push_back("computer copy");
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
    if (lastCommand == "copy")
    {
        hasCompleted = false;
        startTime = ofGetElapsedTimeMillis();
        return true;
    }
    hasCompleted = true;
    return false;
}

void GrabCopyingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    std::string command = speechProcessor.getLastCommand();
    LeapHand* hand = handProcessor.getHandAtIndex(0);
    
    bool isCancelled = false;
    bool lost = false;
    
    if (copyingMode == NONE)
    {
        objectManager.updateHighlight(hand->getTipLocation());
    }

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
                         // Try activate
                        AirObject* highlightedObject = objectManager.getHighlightedObject();
                        if (highlightedObject)
                        {
                            copiedObject = highlightedObject;
                            AirCommandCopying* cmd = new AirCommandCopying(objectManager, copiedObject);
                            if (!controller->pushCommand(cmd))
                            {
                                Logger::getInstance()->temporaryLog("COPYing object " + copiedObject->getDescription() + "failed; cannot allocate new copy");
                            }
                            objectCopy = cmd->getObjectCopy();
                            copyingMode = DRAW;
                        }
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
            lost = false;
        }
    }
    if (hasCompleted) {
        if (isCancelled) {
            if (NULL != copiedObject) {
                controller->popCommand();                
            }
        }
        copyingMode = NONE;
        copiedObject = NULL;
        objectCopy = NULL;
        Logger::getInstance()->logToFile(isCancelled ? cancelTag : (lost ? lostTag : completeTag), startTime, ofGetElapsedTimeMillis());
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