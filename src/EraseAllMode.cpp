//
//  EraseAllMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/27/15.
//
//

#include "EraseAllMode.h"

#include "AirCommandEraseAll.h"
#include "Logger.h"

std::vector<std::string> EraseAllMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer erase all");
    commands.push_back("computer delete all");
    
    return commands;
}


EraseAllMode::EraseAllMode() : AirControlMode()
{
    
}

EraseAllMode::~EraseAllMode()
{
    
}

void EraseAllMode::drawMode()
{
    
}

bool EraseAllMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if ((lastCommand == "erase all") || (lastCommand == "delete all"))
    {
        AirCommandEraseAll* cmd = new AirCommandEraseAll(objectManager);
        if (!controller->pushCommand(cmd))
        {
            Logger::getInstance()->temporaryLog("Erase all object FAILED failed; cannot allocate new copy");
            return false;
        }
        
        Logger::getInstance()->temporaryLog("Erase all object SUCCEEDED");
        hasCompleted = true;
        return true;
    }
    return false;
}

void EraseAllMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string EraseAllMode::getStatusMessage()
{
    return "Erase all objects";
}

std::string EraseAllMode::getHelpMessage()
{
    std::string msg = "";
    //"1. Say 'computer erase (or delete) all to delete all objects'.";
    return msg;
}