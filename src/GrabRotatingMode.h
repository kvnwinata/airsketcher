//
//  GrabRotatingMode.h
//  airsketcher
//
//  Created by Kevin Wong on 4/3/15.
//
//

#ifndef __airsketcher__GrabRotatingMode__
#define __airsketcher__GrabRotatingMode__

#include "AirController.h"

class GrabRotatingMode : public AirControlMode
{
public:
    
    GrabRotatingMode();
    ~GrabRotatingMode();
    
    bool tryActivateMode(AirController* controller, HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(AirController* controller, HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
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


#endif /* defined(__airsketcher__GrabRotatingMode__) */
