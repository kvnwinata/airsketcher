//
//  AirControlMode.h
//  airsketcher
//
//  Created by Kevin Wong on 3/22/15.
//
//

#ifndef __airsketcher__AirControlMode__
#define __airsketcher__AirControlMode__

#include "HandProcessor.h"
#include "SpeechProcessor.h"
#include "AirObjectManager.h"


class AirControlMode
{
    
public:
    
    AirControlMode();
    virtual ~AirControlMode();
    
    virtual bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) = 0;
    virtual void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) = 0;
    virtual void drawMode() const = 0;
    
    bool getHasCompleted() const;
    
    virtual std::string getStatusMessage() = 0;

    
protected:
    bool hasCompleted;
};

#endif /* defined(__airsketcher__AirControlMode__) */
