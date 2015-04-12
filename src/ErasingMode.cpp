//
//  ErasingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "ErasingMode.h"
#include "Logger.h"

std::vector<std::string> ErasingMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer erase this");
    commands.push_back("computer delete this");
    
    return commands;
}


ErasingMode::ErasingMode() : AirControlMode()
{
    
}

ErasingMode::~ErasingMode()
{
    
}

void ErasingMode::drawMode()
{
    
}

bool ErasingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if ((lastCommand == "erase this") || (lastCommand == "delete this"))
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            std::string objectDescription = highlightedObject->getDescription();
            objectManager.deleteObject(highlightedObject);
            Logger::getInstance()->temporaryLog("ERASE: " + objectDescription);
            
            hasCompleted = true;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'ERASE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void ErasingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string ErasingMode::getStatusMessage()
{
    return "ERASING xxx";
}

std::string ErasingMode::getHelpMessage()
{
    std::string msg = "1. Point at the object you'd like to delete. \n"
    "2. And then say 'computer erase this'.";
    return msg;
}

