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

AirController::AirController() : currentMode(NULL)
{
    modes.push_back(new ColoringMode());
    modes.push_back(new CopyingMode());
    modes.push_back(new CylinderCreatingMode());
    modes.push_back(new ErasingMode());
    modes.push_back(new MovingMode());
    modes.push_back(new SphereCreatingMode());
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