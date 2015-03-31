//
//  ErasingMode.cpp
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#include "ErasingMode.h"
#include "Logger.h"

ErasingMode::ErasingMode() : AirControlMode()
{
    
}

ErasingMode::~ErasingMode()
{
    
}

void ErasingMode::drawMode() const
{
    
}

bool ErasingMode::tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager)
{
    std::string commandString = lastCommand.substr(0,10);
    if (commandString == "erase this")
    {
        // try activate
        AirObject * highlightedObject = objectManager.getHighlightedObject();
        
        if (highlightedObject)
        {
            std::string objectDescription = highlightedObject->getDescription();
            objectManager.deleteObject(highlightedObject);
            Logger::getInstance()->temporaryLog("ERASE: " + objectDescription);
            
            hasCompleted = true;
            return true;
        }
        else
        {
            Logger::getInstance()->temporaryLog("No object selected; select object then say 'ERASE THIS'");
            hasCompleted = true;
            return false;
        }
    }
    return false;
}

void ErasingMode::update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager)
{
    
}

std::string ErasingMode::getStatusMessage()
{
    return "ERASING xxx";
}
