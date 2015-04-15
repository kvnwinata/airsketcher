//
//  AirControlMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/15/15
//
//

#include "AirControlMode.h"

AirControlMode::AirControlMode()
: hasCompleted(true)
{
    
}

AirControlMode::~AirControlMode()
{
    for (AirCommand* cmd : undoCommands)
    {
        delete cmd;
    }
    undoCommands.clear();
    
    for (AirCommand* cmd : redoCommands)
    {
        delete cmd;
    }
    redoCommands.clear();
}

bool AirControlMode::getHasCompleted() const
{
    return hasCompleted;
}

std::string AirControlMode::getHelpMessage()
{
    return "Help message not implemented for this mode!";
}

bool AirControlMode::pushCommand(AirCommand* cmd) {
    if (!cmd->execute()) {
        return false;
    }
    undoCommands.push_back(cmd);
    
    for (AirCommand* redoCmd : redoCommands)
    {
        delete redoCmd;
    }
    redoCommands.clear();
    return true;
};

// Pop the command on the top of the undoCommands stack and call unexecute
void AirControlMode::popCommand() {
    AirCommand* cmd = undoCommands.back();
    cmd->unexecute();
    delete cmd;
    undoCommands.pop_back();
};
