//
//  LineCreatingMode.cpp
//  airsketcher
//
//  Created by Pramod Kandel on 4/6/15.
//
//

#include "LineCreatingMode.h"
#include "logger.h"

std::vector<std::string> LineCreatingMode::getCommands()
{
    std::vector<std::string> commands;
    commands.push_back("computer draw line");
    commands.push_back("computer done");
    commands.push_back("computer cancel");
    return commands;
}

LineCreatingMode::LineCreatingMode() : AirControlMode()
{
    
}

LineCreatingMode::~LineCreatingMode()
{
    
}

void LineCreatingMode::drawMode()
{
    
}


bool LineCreatingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{

    return false;
}

void LineCreatingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{

}

std::string LineCreatingMode::getStatusMessage()
{
    return "Creating a line";
}