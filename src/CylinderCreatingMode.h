//
//  CylinderCreatingMode.h
//  airsketcher
//
//  Created by Patricia Suriana on 3/31/15.
//
//

#ifndef __airsketcher__CylinderCreatingMode__
#define __airsketcher__CylinderCreatingMode__

#include "AirControlMode.h"

class CylinderCreatingMode : public AirControlMode
{
public:
    
    CylinderCreatingMode();
    ~CylinderCreatingMode();
    
    bool tryActivateMode(HandProcessor &handProcessor, std::string lastCommand, AirObjectManager &objectManager) override;
    void update(HandProcessor &handProcessor, SpeechProcessor &speechProcessor, AirObjectManager &objectManager) override;
    void drawMode() const override;
    
    std::string getStatusMessage() override;
    
private:
    
    AirObject * movingObject;
    
    ofPoint relativePosition;
    ofPoint originalPosition;
};

#endif /* defined(__airsketcher__CylinderCreatingMode__) */
