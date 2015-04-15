//
//  AirControlMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//  Last update by Patricia Suriana on 4/14/15
//
//

#ifndef __airsketcher__AirControlMode__
#define __airsketcher__AirControlMode__

#include <vector>

#include "HandProcessor.h"
#include "SpeechProcessor.h"
#include "AirCommand.h"
#include "AirController.h"
#include "AirObjectManager.h"

class AirControlMode
{
    
public:
    
    AirControlMode();
    virtual ~AirControlMode();
    
    virtual bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) = 0;
    virtual void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) = 0;
    virtual void drawMode() = 0;
    virtual std::vector<std::string> getCommands() = 0;
    
    bool getHasCompleted() const;
    
    virtual std::string getStatusMessage() = 0;
    virtual std::string getHelpMessage();
    
protected:
    bool hasCompleted;
};

#endif /* defined(__airsketcher__AirControlMode__) */
