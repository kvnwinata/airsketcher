//
//  SphereCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__SphereCreatingMode__
#define __airsketcher__SphereCreatingMode__

#include "AirControlMode.h"

class SphereCreatingMode : public AirControlMode
{
public:
    
    SphereCreatingMode();
    ~SphereCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() override;
    std::vector<std::string> getCommands();

    std::string getStatusMessage() override;
    
private:
    
    AirObject * movingObject;
    
    ofPoint relativePosition;
    ofPoint originalPosition;
};

#endif /* defined(__airsketcher__SphereCreatingMode__) */
