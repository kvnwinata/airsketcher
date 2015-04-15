//
//  UndoRedoMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 4/14/15.
//
//

#include "UndoRedoMode.h"
#include "Logger.h"

std::vector<std::string> UndoRedoMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer undo one");
    commands.push_back("computer redo one");
    commands.push_back("computer undo two");
    commands.push_back("computer redo two");
    commands.push_back("computer undo three");
    commands.push_back("computer redo three");
    commands.push_back("computer undo four");
    commands.push_back("computer redo four");
    return commands;
}


UndoRedoMode::UndoRedoMode() : AirControlMode()
{
    
}

UndoRedoMode::~UndoRedoMode()
{
    
}

void UndoRedoMode::drawMode()
{
    
}

bool UndoRedoMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
	std::string commandString = lastCommand.substr(0,4);
    if (commandString == "undo")
    {
    	std::string levelsString = lastCommand.substr(5);
    	undo(controller, getLevelsFromString(levelsString));
        Logger::getInstance()->temporaryLog("UNDO " + levelsString);
        hasCompleted = true;
        return true;
    } 
    else if (commandString == "redo") 
    {
    	std::string levelsString = lastCommand.substr(5);
    	redo(controller, getLevelsFromString(levelsString));
    	Logger::getInstance()->temporaryLog("REDO " + levelsString);
        hasCompleted = true;
        return true;
    }
    return false;
}

void UndoRedoMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

int UndoRedoMode::getLevelsFromString(std::string stringLevels)
{
	if (stringLevels == "one")
    {
        return 1;
    }
    else if (stringLevels == "two")
    {
        return 2;
    }
    else if (stringLevels == "three")
    {
        return 3;
    }
    else if (stringLevels == "four")
    {
        return 4;
    }
    return 0;
}

void UndoRedoMode::undo(AirController* controller, int levels)
{
    controller->undoCommands(levels);
}

void UndoRedoMode::redo(AirController* controller, int levels)
{
	controller->redoCommands(levels);
}

std::string UndoRedoMode::getStatusMessage()
{
    return "UNDO/REDO xxx";
}

std::string UndoRedoMode::getHelpMessage()
{
    std::string msg = "";
    return msg;
}