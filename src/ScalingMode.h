//
//  ScalingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__ScalingMode__
#define __airsketcher__ScalingMode__

#include "AirControlMode.h"

class ScalingMode : public AirControlMode
{
public:
    
    ScalingMode();
    ~ScalingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    
private:
    
    AirObject * scalingObject;
    
    
    ofPoint originalCenterOfScaling;
    ofPoint originalPosition;
    ofPoint relativePosition;
        
    float originalScale;
    
    const float scalingParameter = 50.f;
};

#endif /* defined(__airsketcher__ScalingMode__) */
