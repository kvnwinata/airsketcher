//
//  AirController.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//  Last update by Patricia Suriana on 4/15/15
//
//

#include "AirController.h"

#include "ColoringMode.h"
#include "CopyingMode.h"
#include "CylinderCreatingMode.h"
#include "SphereCreatingMode.h"
#include "ErasingMode.h"
#include "MovingMode.h"
#include "ResizingMode.h"
#include "RotatingMode.h"
#include "SpaceRotatingMode.h"
#include "LineCreatingMode.h"
#include "BoxCreatingMode.h"
#include "UndoRedoMode.h"
#include "EraseAllMode.h"
#include "GrabMovingMode.h"
#include "GrabResizingmode.h"
#include "SnapObjectsMode.h"
#include "GrabCopyingMode.h"
#include "GrabCylinderCreatingMode.h"
#include "GrabSphereCreatingMode.h"
#include "GrabRotatingMode.h"
#include "GrabBoxCreatingMode.h"
#include "GrabLineCreatingMode.h"
#include "GrabSnapObjectsMode.h"
#include "Logger.h"

AirController::AirController() : currentMode(NULL)
{
    if (Logger::getInstance()->getIsSystemGrab())
    {
        modes.push_back(new GrabMovingMode());
        modes.push_back(new GrabResizingMode());
        modes.push_back(new GrabRotatingMode());
        
        modes.push_back(new GrabCopyingMode());
        modes.push_back(new GrabCylinderCreatingMode());
        modes.push_back(new GrabSphereCreatingMode());
        
        modes.push_back(new GrabLineCreatingMode());
        modes.push_back(new GrabSnapObjectsMode());
        modes.push_back(new GrabBoxCreatingMode());
    }
    else
    {
        modes.push_back(new MovingMode());
        modes.push_back(new ResizingMode());
        modes.push_back(new RotatingMode());
        
        modes.push_back(new CopyingMode());
        modes.push_back(new CylinderCreatingMode());
        modes.push_back(new SphereCreatingMode());

        modes.push_back(new LineCreatingMode());
        modes.push_back(new BoxCreatingMode());
        modes.push_back(new SnapObjectsMode());
    }
    
    modes.push_back(new ColoringMode());
    modes.push_back(new ErasingMode());
    modes.push_back(new EraseAllMode());
    modes.push_back(new UndoRedoMode());
    modes.push_back(new SpaceRotatingMode());
}

AirController::~AirController()
{
    for (AirCommand* cmd : undoStack)
    {
        delete cmd;
    }
    undoStack.clear();
    
    for (AirCommand* cmd : redoStack)
    {
        delete cmd;
    }
    redoStack.clear();
    
    for (AirControlMode* mode : modes) {
        delete mode;
    }
    modes.clear();
}


bool AirController::pushCommand(AirCommand* cmd) {
    if (!cmd->execute()) {
        return false;
    }
    undoStack.push_back(cmd);
    
    for (AirCommand* redoCmd : redoStack)
    {
        delete redoCmd;
    }
    redoStack.clear();
    return true;
}

// Pop the command on the top of the undoStack stack and call unexecute
void AirController::popCommand() {
    AirCommand* cmd = undoStack.back();
    cmd->unexecute();
    delete cmd;
    undoStack.pop_back();
}

void AirController::undoCommands(int levels)
{
    for (int i = 0; i < levels; ++i)
    {
        if (undoStack.size() == 0) {
            return;
        }
        AirCommand* cmd = undoStack.back();
        undoStack.pop_back();
        cmd->unexecute();
        redoStack.push_back(cmd);
    }
}

void AirController::redoCommands(int levels)
{
    for (int i = 0; i < levels; ++i)
    {
        if (redoStack.size() == 0)
        {
            return;
        }
        AirCommand* cmd = redoStack.back();
        redoStack.pop_back();
        cmd->execute();
        undoStack.push_back(cmd);
    }
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
            currentMode->update(this, handProcessor, speechProcessor, objectManager);
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
        if (mode->tryActivateMode(this, handProcessor, command, objectManager))
        {
            currentMode = mode;
            break;
        }
    }
}

std::string AirController::getStatusMessage()
{
    std::stringstream msg;
    if (currentMode)
    {
        msg << currentMode->getStatusMessage();
    }
    else
    {
        msg << "No Currently Active Mode";
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
    
    msg << "Press 'h' for help on available voice commands.";
    
    return msg.str();
}
