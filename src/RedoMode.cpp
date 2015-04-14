//
//  RedoMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "RedoMode.h"
#include "Logger.h"

std::vector<std::string> RedoMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer redo");
    
    return commands;
}


RedoMode::RedoMode() : AirControlMode()
{
    
}

RedoMode::~RedoMode()
{
    
}

void RedoMode::drawMode()
{
    
}

bool RedoMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "redo")
    {
        Logger::getInstance()->temporaryLog("REDO");
        hasCompleted = true;
        return true;
    }
    return false;
}

void RedoMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string RedoMode::getStatusMessage()
{
    return "REDOING xxx";
}

std::string RedoMode::getHelpMessage()
{
    std::string msg = "";
    return msg;
}
