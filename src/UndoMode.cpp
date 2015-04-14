//
//  UndoMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "UndoMode.h"
#include "Logger.h"

std::vector<std::string> UndoMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer undo");
    
    return commands;
}


UndoMode::UndoMode() : AirControlMode()
{
    
}

UndoMode::~UndoMode()
{
    
}

void UndoMode::drawMode()
{
    
}

bool UndoMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    if (lastCommand == "undo")
    {
        Logger::getInstance()->temporaryLog("UNDO");
        hasCompleted = true;
        return true;
    }
    return false;
}

void UndoMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string UndoMode::getStatusMessage()
{
    return "UNDOING xxx";
}

std::string UndoMode::getHelpMessage()
{
    std::string msg = "";
    return msg;
}