//
//  BoxCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#include "BoxCreatingMode.h"
#include "logger.h"

std::vector<std::string> BoxCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw box");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

BoxCreatingMode::BoxCreatingMode() : AirControlMode()
{
    
}

BoxCreatingMode::~BoxCreatingMode()
{
    
}

void BoxCreatingMode::drawMode()
{
    
}

bool BoxCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    
    return false;
}

void BoxCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string BoxCreatingMode::getStatusMessage()
{
    return "Creating a box";
}