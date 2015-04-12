//
//  AirController.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//  Last update by Patricia Suriana on 3/31/15
//
//

#include "AirController.h"

#include "ColoringMode.h"
#include "CopyingMode.h"
#include "CylinderCreatingMode.h"
#include "ErasingMode.h"
#include "MovingMode.h"
#include "SphereCreatingMode.h"
#include "ResizingMode.h"
#include "RotatingMode.h"
#include "SpaceRotatingMode.h"
#include "LineCreatingMode.h"
#include "BoxCreatingMode.h"

AirController::AirController() : currentMode(NULL)
{
    modes.push_back(new ColoringMode());
    modes.push_back(new CopyingMode());
    modes.push_back(new CylinderCreatingMode());
    modes.push_back(new ErasingMode());
    modes.push_back(new MovingMode());
    modes.push_back(new SphereCreatingMode());
    modes.push_back(new ResizingMode());
    modes.push_back(new RotatingMode());
    modes.push_back(new SpaceRotatingMode());
    modes.push_back(new LineCreatingMode());
    modes.push_back(new BoxCreatingMode());
}

AirController::~AirController()
{
    for (AirControlMode* mode : modes) {
        delete mode;
    }
    modes.clear();
}

void AirController::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    if (currentMode)
    {
        if (currentMode->getHasCompleted())
        {
            currentMode = NULL;
        }
        else
        {
            currentMode->update(handProcessor, speechProcessor, objectManager);
        }
        return;
    }
    
    // update objects
    LeapHand* hand0 =  handProcessor.getHandAtIndex(0);
    //LeapHand* hand1 =  handProcessor.getHandAtIndex(1);
    
    if (hand0->getIsActive())
    {
        ofPoint tipLocation = hand0->getTipLocation();
        objectManager.updateHighlight(tipLocation);
    }
    
    // search for active mode:
    std::string command = speechProcessor.getLastCommand();
    for (AirControlMode * mode : modes)
    {
        if (mode->tryActivateMode(handProcessor, command, objectManager))
        {
            currentMode = mode;
            break;
        }
    }
}

std::string AirController::getStatusMessage()
{
    std::stringstream msg;
    msg << "[CONTROL]: ";
    if (currentMode)
    {
        msg << currentMode->getStatusMessage();
    }
    else
    {
        msg << "NO ACTIVE MODE\n";
    }
    
    return msg.str();
}

std::vector<std::string> AirController::getCommands()
{
    std::set<std::string> commandSet; // use set to remove duplicates
    
    for (AirControlMode* mode : modes)
    {
        std::vector<std::string> modeCommands = mode->getCommands();
        for (std::string command : modeCommands)
        {
            commandSet.insert(command);
        }
    }
    
    // convert set back to vectors:
    std::vector<std::string> commands;
    for (std::string command : commandSet)
    {
        commands.push_back(command);
    }
    
    return commands;
}

void AirController::draw()
{
    if (currentMode)
    {
        currentMode->drawMode();
    }
}

std::string AirController::getHelpMessage()
{
    if (currentMode)
    {
        return currentMode->getHelpMessage();
    }
    
    std::stringstream msg;
    
    msg << "Idle help message not implemented!";
    
    return msg.str();
}
