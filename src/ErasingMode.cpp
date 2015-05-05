//
//  ErasingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "ErasingMode.h"

#include "AirCommandErasing.h"
#include "Logger.h"

std::vector<std::string> ErasingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer erase this");
    commands.push_back("computer delete this");
    
    return commands;
}


ErasingMode::ErasingMode() 
: AirControlMode()
, eraseCount(0)
{
    
}

ErasingMode::~ErasingMode()
{
    // TODO: might want to log to different file
    Logger::getInstance()->logToFile("erase-count", eraseCount, 0);
}

void ErasingMode::drawMode()
{
    
}

bool ErasingMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if ((lastCommand == "erase this") || (lastCommand == "delete this"))
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            std::string objectDescription = highlightedObject->getDescription();
            AirCommandErasing* cmd = new AirCommandErasing(objectManager, highlightedObject);
            
            if (!controller->pushCommand(cmd))
            {
                Logger::getInstance()->temporaryLog("ERASING object " + objectDescription + "failed; cannot allocate new copy");
                return false;
            }

            Logger::getInstance()->temporaryLog("ERASE: " + objectDescription);
            hasCompleted = true;
            eraseCount += 1;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'ERASE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    hasCompleted = true;
    return false;
}

void ErasingMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string ErasingMode::getStatusMessage()
{
    return "ERASING xxx";
}

std::string ErasingMode::getHelpMessage()
{
    std::string msg = "";
    //"1. Point at the object you'd like to delete. \n"
    //"2. And then say 'computer erase this'.";
    return msg;
}

