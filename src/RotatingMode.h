//
//  RotatingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__RotatingMode__
#define __airsketcher__RotatingMode__

#include "AirControlMode.h"

class RotatingMode : public AirControlMode
{
public:
    
    RotatingMode();
    ~RotatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    
    std::vector<std::string> getCommands();
    
    std::string getStatusMessage() override;
    std::string getHelpMessage() override;
    
private:
    
    AirObject * rotatingObject;
    
    ofVec3f      currentVector;
    ofVec3f      originalVector;
    ofQuaternion originalOrientation;
};


#endif /* defined(__airsketcher__RotatingMode__) */
