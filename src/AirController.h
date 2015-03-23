//
//  AirController.h
//  airsketcher
//
//  Created by Kevin Wong on 3/20/15.
//
//

#ifndef __airsketcher__AirController__
#define __airsketcher__AirController__

#include "ofMain.h"

#include "AirControlMode.h"

class AirController
{
public:
    
    AirController();
    ~AirController();
    
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager);
    
    std::string getStatusMessage();
    
private:
    
    AirControlMode * currentMode;
    
    vector<AirControlMode*> modes;
};

#endif /* defined(__airsketcher__AirController__) */
