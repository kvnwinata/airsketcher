//
//  ColoringMode.cpp
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#include "ColoringMode.h"

#include "AirCommandColoring.h"
#include "Logger.h"

std::vector<std::string> ColoringMode::getCommands()
{
    std::vector<std::string> commands;
    
    commands.push_back("computer color this red");
    commands.push_back("computer color this blue");
    commands.push_back("computer color this green");
    commands.push_back("computer color this yellow");
    commands.push_back("computer color this orange");
    commands.push_back("computer color this purple");
    commands.push_back("computer color this white");
    commands.push_back("computer color this black");
    
    return commands;
}

ColoringMode::ColoringMode() : AirControlMode()
{
    
}

ColoringMode::~ColoringMode()
{
    
}

void ColoringMode::drawMode()
{
    
}

ofColor ColoringMode::getColorFromString(std::string colorString)
{
    if (colorString == "red")
    {
        return ofColor(255,0,0);
    }
    else if (colorString == "blue")
    {
        return ofColor(0,0,255);
    }
    else if (colorString == "green")
    {
        return ofColor(0,255,0);
    }
    else if (colorString == "yellow")
    {
        return ofColor(255,255,0);
    }
    else if (colorString == "orange")
    {
        return ofColor(255,128,0);
    }
    else if (colorString == "purple")
    {
        return ofColor(255,0,255);
    }
    else if (colorString == "white")
    {
        return ofColor(255,255,255);
    }
    else if (colorString == "black")
    {
        return ofColor(40,40,40);
    }
    else
    {
        return ofColor(128,128,128);
    }
}

bool ColoringMode::tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    startTime = ofGetElapsedTimeMillis();
    
    std::string commandString = lastCommand.substr(0,10);
    if (commandString == "color this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();

        if (highlightedObject)
        {
            std::string colorString = lastCommand.substr(11);

            ofColor newColor = getColorFromString(colorString);
            ofColor prevColor = highlightedObject->getColor();            
            AirCommandColoring* cmd = new AirCommandColoring(highlightedObject, prevColor, newColor);
            controller->pushCommand(cmd);

            Logger::getInstance()->temporaryLog("COLORED TO: " + colorString);
            Logger::getInstance()->logToFile(completeTag, startTime, ofGetElapsedTimeMillis());
            hasCompleted = true;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'COLOR THIS [COLOR]' TO COLOR");
            hasCompleted = true;
            return false;
        }
    }
    hasCompleted = true;
    return false;
}

void ColoringMode::update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string ColoringMode::getStatusMessage()
{
    return "COLORING";
}

std::string ColoringMode::getHelpMessage()
{
    std::string msg =
    "";
    //"1. Point at the object you'd like the color to change. \n"
    //"2. And then say 'computer erase [COLOR]'.";
    return msg;
}